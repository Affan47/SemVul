PutZNodes(node_t *root)
{
  uint32_g raw_num = UINT32(num_nodes);

  ZLibAppendLump(&raw_num, 4);
  DisplayTicker();

  node_cur_index = 0;

  if (root)
    PutOneZNode(root);

  if (node_cur_index != num_nodes)
    InternalError("PutZNodes miscounted (%d != %d)",
      node_cur_index, num_nodes);
}
