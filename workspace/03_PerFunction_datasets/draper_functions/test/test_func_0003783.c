emit_mocs_l3cc_table(struct drm_i915_gem_request *req,
				const struct drm_i915_mocs_table *table)
{
	struct intel_ringbuffer *ringbuf = req->ringbuf;
	unsigned int count;
	unsigned int i;
	u32 value;
	u32 filler = (table->table[0].l3cc_value & 0xffff) |
			((table->table[0].l3cc_value & 0xffff) << 16);
	int ret;

	if (WARN_ON(table->size > GEN9_NUM_MOCS_ENTRIES))
		return -ENODEV;

	ret = intel_logical_ring_begin(req, 2 + GEN9_NUM_MOCS_ENTRIES);
	if (ret) {
		DRM_DEBUG("intel_logical_ring_begin failed %d\n", ret);
		return ret;
	}

	intel_logical_ring_emit(ringbuf,
			MI_LOAD_REGISTER_IMM(GEN9_NUM_MOCS_ENTRIES / 2));

	for (i = 0, count = 0; i < table->size / 2; i++, count += 2) {
		value = (table->table[count].l3cc_value & 0xffff) |
			((table->table[count + 1].l3cc_value & 0xffff) << 16);

		intel_logical_ring_emit(ringbuf, GEN9_LNCFCMOCS0 + i * 4);
		intel_logical_ring_emit(ringbuf, value);
	}

	if (table->size & 0x01) {

		value = (table->table[count].l3cc_value & 0xffff) |
			((table->table[0].l3cc_value & 0xffff) << 16);
	} else
		value = filler;


	for (; i < GEN9_NUM_MOCS_ENTRIES / 2; i++) {
		intel_logical_ring_emit(ringbuf, GEN9_LNCFCMOCS0 + i * 4);
		intel_logical_ring_emit(ringbuf, value);

		value = filler;
	}

	intel_logical_ring_emit(ringbuf, MI_NOOP);
	intel_logical_ring_advance(ringbuf);

	return 0;
}
