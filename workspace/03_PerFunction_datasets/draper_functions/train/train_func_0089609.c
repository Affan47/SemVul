guc_init_ctx_desc(struct intel_guc *guc,
			      struct i915_guc_client *client)
{
	struct intel_context *ctx = client->owner;
	struct guc_context_desc desc;
	struct sg_table *sg;
	int i;

	memset(&desc, 0, sizeof(desc));

	desc.attribute = GUC_CTX_DESC_ATTR_ACTIVE | GUC_CTX_DESC_ATTR_KERNEL;
	desc.context_id = client->ctx_index;
	desc.priority = client->priority;
	desc.db_id = client->doorbell_id;

	for (i = 0; i < I915_NUM_RINGS; i++) {
		struct guc_execlist_context *lrc = &desc.lrc[i];
		struct intel_ringbuffer *ringbuf = ctx->engine[i].ringbuf;
		struct intel_engine_cs *ring;
		struct drm_i915_gem_object *obj;
		uint64_t ctx_desc;


		obj = ctx->engine[i].state;
		if (!obj)
			break;

		ring = ringbuf->ring;
		ctx_desc = intel_lr_context_descriptor(ctx, ring);
		lrc->context_desc = (u32)ctx_desc;


		lrc->ring_lcra = i915_gem_obj_ggtt_offset(obj) +
				LRC_STATE_PN * PAGE_SIZE;
		lrc->context_id = (client->ctx_index << GUC_ELC_CTXID_OFFSET) |
				(ring->id << GUC_ELC_ENGINE_OFFSET);

		obj = ringbuf->obj;

		lrc->ring_begin = i915_gem_obj_ggtt_offset(obj);
		lrc->ring_end = lrc->ring_begin + obj->base.size - 1;
		lrc->ring_next_free_location = lrc->ring_begin;
		lrc->ring_current_tail_pointer_value = 0;

		desc.engines_used |= (1 << ring->id);
	}

	WARN_ON(desc.engines_used == 0);


	desc.db_trigger_cpu = 0;
	desc.db_trigger_uk = client->doorbell_offset +
		i915_gem_obj_ggtt_offset(client->client_obj);
	desc.db_trigger_phy = client->doorbell_offset +
		sg_dma_address(client->client_obj->pages->sgl);

	desc.process_desc = client->proc_desc_offset +
		i915_gem_obj_ggtt_offset(client->client_obj);

	desc.wq_addr = client->wq_offset +
		i915_gem_obj_ggtt_offset(client->client_obj);

	desc.wq_size = client->wq_size;


	desc.desc_private = (uintptr_t)client;


	sg = guc->ctx_pool_obj->pages;
	sg_pcopy_from_buffer(sg->sgl, sg->nents, &desc, sizeof(desc),
			     sizeof(desc) * client->ctx_index);
}
