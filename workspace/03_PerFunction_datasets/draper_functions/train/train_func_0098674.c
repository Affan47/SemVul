seq_point_info_free (gpointer value)
{
	int i = 0;
	MonoSeqPointInfo* info = (MonoSeqPointInfo*)value;

	for (i = 0; i < info->len; ++i) {
		SeqPoint *sp = &info->seq_points [i];
		g_free (sp->next);
	}

	g_free (info);
}
