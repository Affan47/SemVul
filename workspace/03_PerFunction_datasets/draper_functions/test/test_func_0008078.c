nemo_directory_add_file_to_work_queue (NemoDirectory *directory,
					   NemoFile *file)
{
	g_return_if_fail (file->details->directory == directory);

	nemo_file_queue_enqueue (directory->details->high_priority_queue,
				     file);
}
