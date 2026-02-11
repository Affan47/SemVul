eval_match_nexthop(struct fttag_action *fta,
  struct fts3rec_v1005 *rec)
{
  struct ftchash *ftch;
  u_int32 hash, ipaddr;
  struct fttag_next_hop_look *nh_look;
  u_int16 set_tmp;

  ftch = fta->look;
  ipaddr = rec->nexthop;

  hash = (ipaddr>>16) ^ (ipaddr & 0xFFFF);
  hash = (hash>>8) ^ (hash & 0xFF);


  nh_look = ftchash_lookup(ftch, &ipaddr, hash);

  if (nh_look) {

    set_tmp = nh_look->set_flags;

    if (set_tmp & FT_TAG_SET_DST_TAG)
      rec->dst_tag = nh_look->dst_tag;
    else if (set_tmp & FT_TAG_OR_DST_TAG)
      rec->dst_tag |= nh_look->dst_tag;

    if (set_tmp & FT_TAG_SET_SRC_TAG)
      rec->src_tag = nh_look->src_tag;
    else if (set_tmp & FT_TAG_OR_SRC_TAG)
      rec->src_tag |= nh_look->src_tag;

  }

}
