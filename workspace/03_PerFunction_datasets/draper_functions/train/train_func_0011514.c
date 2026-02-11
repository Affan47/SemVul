vxml_expand_pe_entity(vxml_parser_t *vp, const char *name, bool inquote)
{
	bool ret;


	if (!inquote) {
		struct vxml_buffer *vb;
		static char vxc_sp_buf[] = " ";


		vb = vxml_buffer_alloc(vp->generation++,
				vxc_sp_buf, CONST_STRLEN(vxc_sp_buf),
				FALSE, FALSE, utf8_decode_char_buffer);
		vp->input = g_slist_prepend(vp->input, vb);
	}

	ret = vxml_expand(vp, name, vp->pe_entities);

	if (ret && !inquote)
		vxml_unread_char(vp, VXC_SP);

	return ret;
}
