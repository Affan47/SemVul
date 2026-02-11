persistent_ram_zap(struct persistent_ram_zone *prz)
{
	atomic_set(&prz->buffer->start, 0);
	atomic_set(&prz->buffer->size, 0);
	persistent_ram_update_header_ecc(prz);
}
