radeon_ring_backup(struct radeon_device *rdev, struct radeon_ring *ring,
			    uint32_t **data)
{
	unsigned size, ptr, i;


	mutex_lock(&rdev->ring_lock);
	*data = NULL;

	if (ring->ring_obj == NULL) {
		mutex_unlock(&rdev->ring_lock);
		return 0;
	}


	if (!radeon_fence_count_emitted(rdev, ring->idx)) {
		mutex_unlock(&rdev->ring_lock);
		return 0;
	}


	if (ring->rptr_save_reg)
		ptr = RREG32(ring->rptr_save_reg);
	else if (rdev->wb.enabled)
		ptr = le32_to_cpu(*ring->next_rptr_cpu_addr);
	else {

		mutex_unlock(&rdev->ring_lock);
		return 0;
	}

	size = ring->wptr + (ring->ring_size / 4);
	size -= ptr;
	size &= ring->ptr_mask;
	if (size == 0) {
		mutex_unlock(&rdev->ring_lock);
		return 0;
	}


	*data = drm_malloc_ab(size, sizeof(uint32_t));
	if (!*data) {
		mutex_unlock(&rdev->ring_lock);
		return 0;
	}
	for (i = 0; i < size; ++i) {
		(*data)[i] = ring->ring[ptr++];
		ptr &= ring->ptr_mask;
	}

	mutex_unlock(&rdev->ring_lock);
	return size;
}
