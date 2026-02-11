im_hangul_handle_direct_mode (GtkIMContextHangul *hcontext,
			      GdkEventKey *key)
{
    if (im_hangul_is_hangul_key (key)) {
	im_hangul_ic_reset(GTK_IM_CONTEXT(hcontext));
	im_hangul_set_input_mode(hcontext, INPUT_MODE_HANGUL);
	return TRUE;
    }
    return FALSE;
}
