set_subnet(TableNode *start_node,
           uint32_t *ip,
           int ip_len,
           int subnet_bits,
           State new_state,
           int delete_children)
{
  int bits_to_go, bits_consumed;
  uint32_t subnet;
  TableNode *node;

  bits_consumed = 0;
  bits_to_go = subnet_bits;
  node = start_node;

  if ((subnet_bits < 0) ||
      (subnet_bits > 32 * ip_len)) {

    return ADF_BADSUBNET;

  } else {

    if ((bits_to_go & (NBITS-1)) == 0) {

      while (bits_to_go > 0) {
        subnet = get_subnet(ip, bits_consumed);
        if (!(node->extended)) {
          open_node(node);
        }
        node = &(node->extended[subnet]);
        bits_to_go -= NBITS;
        bits_consumed += NBITS;
      }

      if (delete_children) {
        close_node(node);
      }
      node->state = new_state;

    } else {
      int N, i, j;
      TableNode *this_node;

      while (bits_to_go >= NBITS) {
        subnet = get_subnet(ip, bits_consumed);
        if (!(node->extended)) {
          open_node(node);
        }
        node = &(node->extended[subnet]);
        bits_to_go -= NBITS;
        bits_consumed += NBITS;
      }


      N = 1 << (NBITS-bits_to_go);
      subnet = get_subnet(ip, bits_consumed);
      if (!(node->extended)) {
        open_node(node);
      }

      for (i=subnet, j=0; j<N; i++, j++) {
        this_node = &(node->extended[i]);
        if (delete_children) {
          close_node(this_node);
        }
        this_node->state = new_state;
      }
    }

    return ADF_SUCCESS;
  }

}
