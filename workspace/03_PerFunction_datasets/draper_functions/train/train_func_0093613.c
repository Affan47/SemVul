desc_obj_fake(int k_idx)
{
	object_kind *kind = &k_info[k_idx];
	object_type object_type_body;
	object_type *o_ptr = &object_type_body;

	char header[120];

	textblock *tb;
	region area = { 0, 0, 0, 0 };


	if (of_has(kind->flags, OF_INSTA_ART) && artifact_is_known(get_artifact_from_kind(kind)))
	{
		desc_art_fake(get_artifact_from_kind(kind));
		return;
	}


	track_object_kind(k_idx);
	handle_stuff(p_ptr);


	object_wipe(o_ptr);


	object_prep(o_ptr, kind, 0, EXTREMIFY);


	if (kind->aware) o_ptr->ident |= (IDENT_STORE);


	if (!kind->flavor) object_notice_everything(o_ptr);


	handle_stuff(p_ptr);

	tb = object_info(o_ptr, OINFO_NONE);
	object_desc(header, sizeof(header), o_ptr,
			ODESC_PREFIX | ODESC_FULL | ODESC_CAPITAL);

	textui_textblock_show(tb, area, header);
	textblock_free(tb);
}
