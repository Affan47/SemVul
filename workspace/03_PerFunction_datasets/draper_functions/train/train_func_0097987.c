BD_DecMultipleReplace(GF_BifsDecoder * codec, GF_BitStream *bs)
{
	GF_Err e;
	u32 NodeID, flag;
	GF_Node *node;

	NodeID = 1 + gf_bs_read_int(bs, codec->info->config.NodeIDBits);
	node = gf_sg_find_node(codec->current_graph, NodeID);
	if (!node) return GF_NON_COMPLIANT_BITSTREAM;

	flag = gf_bs_read_int(bs, 1);
	if (flag) {
		e = gf_bifs_dec_node_mask(codec, bs, node, 0);
	} else {
		e = gf_bifs_dec_node_list(codec, bs, node, 0);
	}
	return e;
}
