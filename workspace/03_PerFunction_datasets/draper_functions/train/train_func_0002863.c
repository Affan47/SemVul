nemo_file_monitor_remove (NemoFile *file,
			      gconstpointer client)
{
	g_return_if_fail (NEMO_IS_FILE (file));
	g_return_if_fail (client != NULL);

	NEMO_FILE_CLASS (G_OBJECT_GET_CLASS (file))->monitor_remove (file, client);
}
