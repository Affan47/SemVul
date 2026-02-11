queue_shared_file_for_sha1_computation(shared_file_t *sf)
{
	int inserted;

 	shared_file_check(sf);

	inserted = verify_sha1_enqueue(FALSE, shared_file_path(sf),
					shared_file_size(sf), huge_verify_callback,
					shared_file_ref(sf));

	if (!inserted)
		shared_file_unref(&sf);
}
