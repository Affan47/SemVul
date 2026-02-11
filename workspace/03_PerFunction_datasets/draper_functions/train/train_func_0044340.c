vxml_unread_char(vxml_parser_t *vp, uint32 uc)
{
	g_assert(vp->unread_offset < G_N_ELEMENTS(vp->unread));
	g_assert(size_is_non_negative(vp->unread_offset));

	vp->unread[vp->unread_offset++] = uc;

	if (vxml_debugging(19)) {
		vxml_parser_debug(vp, "unread U+%X '%c'", uc,
			is_ascii_print(uc) ? uc & 0xff : ' ');
	}
}
