gf_bifs_get_aq_info(GF_Node *Node, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (Node->sgprivate->tag) {
	case TAG_ProtoNode: return gf_sg_proto_get_aq_info(Node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	default: return gf_sg_mpeg4_node_get_aq_info(Node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	}
}
