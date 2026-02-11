a2dp_unregister_sep(struct a2dp_sep *sep)
{
	if (sep->destroy) {
		sep->destroy(sep->user_data);
		sep->endpoint = NULL;
	}

	avdtp_unregister_sep(sep->lsep);
	g_free(sep);
}
