write_message(pmsg_t *mb, const void *head, const void *data, uint32 size)
{
	size_t written;

	written = pmsg_write(mb, head, GTA_HEADER_SIZE);
	written += pmsg_write(mb, data, size - GTA_HEADER_SIZE);

	g_assert(written == size);
}
