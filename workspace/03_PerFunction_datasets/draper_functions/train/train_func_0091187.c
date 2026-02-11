_scsifront_put_rqid(struct vscsifrnt_info *info, uint32_t id)
{
	int empty = bitmap_empty(info->shadow_free_bitmap, VSCSIIF_MAX_REQS);

	__set_bit(id, info->shadow_free_bitmap);
	info->shadow[id] = NULL;

	return empty || info->wait_ring_available;
}
