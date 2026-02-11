vxml_expand_reference(vxml_parser_t *vp, bool charonly)
{
	uint32 uc;

	g_assert(0 == vxml_output_size(&vp->entity));


	uc = vxml_next_char(vp);
	if (0 == uc) {
		vxml_fatal_error(vp, VXML_E_TRUNCATED_INPUT);
		return FALSE;
	} else if (VXC_SHARP == uc) {
		return vxml_expand_char_ref(vp);
	}


	if (charonly) {
		vxml_output_append(&vp->out, VXC_AMP);
		vxml_unread_char(vp, uc);
		return TRUE;
	}


	if (!vxml_parser_handle_name(vp, &vp->entity, uc))
		return FALSE;

	uc = vxml_next_char(vp);
	if (VXC_SC != uc) {
		vxml_fatal_error_uc(vp, VXML_E_INVALID_NAME_CHARACTER, uc);
		return FALSE;
	}


	uc = vxml_get_default_entity(vxml_output_start(&vp->entity));
	if (uc != 0) {
		vxml_output_append(&vp->out, uc);

		if (vxml_debugging(19)) {
			vxml_parser_debug(vp, "default entity ref: U+%X '%c'", uc,
				is_ascii_print(uc) ? uc & 0xff : ' ');
		}

		goto done;
	}


	if (!vxml_expand_entity(vp, vxml_output_start(&vp->entity)))
		return FALSE;

done:
	vxml_output_discard(&vp->entity);
	return TRUE;
}
