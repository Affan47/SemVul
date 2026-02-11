aub_write_bo(drm_intel_bo *bo)
{
	drm_intel_bo_gem *bo_gem = (drm_intel_bo_gem *) bo;
	uint32_t offset = 0;
	unsigned i;

	aub_bo_get_address(bo);


	for (i = 0; i < bo_gem->aub_annotation_count; ++i) {
		drm_intel_aub_annotation *annotation =
			&bo_gem->aub_annotations[i];
		uint32_t ending_offset = annotation->ending_offset;
		if (ending_offset > bo->size)
			ending_offset = bo->size;
		if (ending_offset > offset) {
			aub_write_large_trace_block(bo, annotation->type,
						    annotation->subtype,
						    offset,
						    ending_offset - offset);
			offset = ending_offset;
		}
	}


	if (offset < bo->size) {
		aub_write_large_trace_block(bo, AUB_TRACE_TYPE_NOTYPE, 0,
					    offset, bo->size - offset);
	}
}
