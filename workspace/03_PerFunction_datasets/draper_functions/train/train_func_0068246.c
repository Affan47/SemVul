vxml_fatal_error(vxml_parser_t *vp, vxml_error_t error)
{
	if (vp->flags & VXML_F_FATAL_ERROR)
		return;

	if (vxml_debugging(0)) {
		g_warning("VXML %s: FATAL error: %s",
			vxml_document_where(vp), vxml_strerror(error));
	}

	vxml_record_fatal_error(vp, error);
}
