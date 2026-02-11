delete_file (GFile           *key,
             GitgChangedFile *value,
             GitgCommit      *commit)
{
	if (!g_object_get_data (G_OBJECT (value), CAN_DELETE_KEY))
	{
		return FALSE;
	}

	g_signal_emit (commit, commit_signals[REMOVED], 0, value);
	return TRUE;
}
