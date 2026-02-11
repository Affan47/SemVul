nemo_merged_directory_add_real_directory (NemoMergedDirectory *merged,
					      NemoDirectory *real_directory)
{
	g_return_if_fail (NEMO_IS_MERGED_DIRECTORY (merged));
	g_return_if_fail (NEMO_IS_DIRECTORY (real_directory));
	g_return_if_fail (!NEMO_IS_MERGED_DIRECTORY (real_directory));


	if (g_list_find (merged->details->directories, real_directory) != NULL) {
		return;
	}

	g_signal_emit (merged, signals[ADD_REAL_DIRECTORY], 0, real_directory);
}
