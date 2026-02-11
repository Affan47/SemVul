r100_debugfs_cp_ring_info(struct seq_file *m, void *data)
{
	struct drm_info_node *node = (struct drm_info_node *) m->private;
	struct drm_device *dev = node->minor->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	uint32_t rdp, wdp;
	unsigned count, i, j;

	radeon_ring_free_size(rdev, ring);
	rdp = RREG32(RADEON_CP_RB_RPTR);
	wdp = RREG32(RADEON_CP_RB_WPTR);
	count = (rdp + ring->ring_size - wdp) & ring->ptr_mask;
	seq_printf(m, "CP_STAT 0x%08x\n", RREG32(RADEON_CP_STAT));
	seq_printf(m, "CP_RB_WPTR 0x%08x\n", wdp);
	seq_printf(m, "CP_RB_RPTR 0x%08x\n", rdp);
	seq_printf(m, "%u free dwords in ring\n", ring->ring_free_dw);
	seq_printf(m, "%u dwords in ring\n", count);
	if (ring->ready) {
		for (j = 0; j <= count; j++) {
			i = (rdp + j) & ring->ptr_mask;
			seq_printf(m, "r[%04d]=0x%08x\n", i, ring->ring[i]);
		}
	}
	return 0;
}
