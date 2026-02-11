pcap_cleanup_linux_mmap( pcap_t *handle )
{
	destroy_ring(handle);
	if (handle->md.oneshot_buffer != NULL) {
		free(handle->md.oneshot_buffer);
		handle->md.oneshot_buffer = NULL;
	}
	pcap_cleanup_linux(handle);
}
