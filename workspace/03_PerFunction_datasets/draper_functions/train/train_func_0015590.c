BD_DecMultipleIndexReplace(GF_BifsDecoder * codec, GF_BitStream *bs)
{
	u32 ID, ind, field_ind, NumBits, lenpos, lennum, count, pos;
	GF_Node *node, *new_node;
	GF_Err e;
	GF_FieldInfo field, sffield;

	ID = 1 + gf_bs_read_int(bs, codec->info->config.NodeIDBits);
	node = gf_sg_find_node(codec->current_graph, ID);
	if (!node) return GF_NON_COMPLIANT_BITSTREAM;
	NumBits = gf_get_bit_size(gf_node_get_num_fields_in_mode(node, GF_SG_FIELD_CODING_IN)-1);
	ind = gf_bs_read_int(bs, NumBits);
	e = gf_bifs_get_field_index(node, ind, GF_SG_FIELD_CODING_IN, &field_ind);
	if (e) return e;
	e = gf_node_get_field(node, field_ind, &field);
	if (gf_sg_vrml_is_sf_field(field.fieldType)) return GF_NON_COMPLIANT_BITSTREAM;

	lenpos = gf_bs_read_int(bs, 5);
	lennum = gf_bs_read_int(bs, 5);
	count = gf_bs_read_int(bs, lennum);


	if (field.fieldType == GF_SG_VRML_MFNODE) {
		while (count) {
			pos = gf_bs_read_int(bs, lenpos);

			new_node = gf_bifs_dec_node(codec, bs, field.NDTtype);
			if (!new_node) return codec->LastError;
			e = gf_node_register(new_node, node);
			if (e) return e;

			e = gf_node_replace_child(node, (GF_ChildNodeItem**) field.far_ptr, pos, new_node);
			count--;
		}
		if (!e) gf_bifs_check_field_change(node, &field);
		return e;
	}

	memcpy(&sffield, &field, sizeof(GF_FieldInfo));
	sffield.fieldType = gf_sg_vrml_get_sf_type(field.fieldType);

	while (count) {
		pos = gf_bs_read_int(bs, lenpos);

		if (pos && pos >= ((GenMFField *)field.far_ptr)->count) {
			pos = ((GenMFField *)field.far_ptr)->count - 1;
		}

		e = gf_sg_vrml_mf_get_item(field.far_ptr, field.fieldType, & sffield.far_ptr, pos);
		if (e) return e;
		e = gf_bifs_dec_sf_field(codec, bs, node, &sffield, 0);
		if (e) break;
		count--;
	}
	if (!e) gf_bifs_check_field_change(node, &field);
	return e;
}
