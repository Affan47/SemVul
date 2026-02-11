select_doorbell_cacheline(struct intel_guc *guc)
{
	const uint32_t cacheline_size = cache_line_size();
	uint32_t offset;

	spin_lock(&guc->host2guc_lock);


	offset = offset_in_page(guc->db_cacheline);


	guc->db_cacheline += cacheline_size;

	spin_unlock(&guc->host2guc_lock);

	DRM_DEBUG_DRIVER("selected doorbell cacheline 0x%x, next 0x%x, linesize %u\n",
			offset, guc->db_cacheline, cacheline_size);

	return offset;
}
