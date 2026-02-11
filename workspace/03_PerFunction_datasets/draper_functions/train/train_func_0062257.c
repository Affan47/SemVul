i915_gem_init_hw(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_engine_cs *engine;
	int ret, j;


	intel_uncore_forcewake_get(dev_priv, FORCEWAKE_ALL);

	if (HAS_EDRAM(dev) && INTEL_GEN(dev_priv) < 9)
		I915_WRITE(HSW_IDICR, I915_READ(HSW_IDICR) | IDIHASHMSK(0xf));

	if (IS_HASWELL(dev))
		I915_WRITE(MI_PREDICATE_RESULT_2, IS_HSW_GT3(dev) ?
			   LOWER_SLICE_ENABLED : LOWER_SLICE_DISABLED);

	if (HAS_PCH_NOP(dev)) {
		if (IS_IVYBRIDGE(dev)) {
			u32 temp = I915_READ(GEN7_MSG_CTL);
			temp &= ~(WAIT_FOR_PCH_FLR_ACK | WAIT_FOR_PCH_RESET_ACK);
			I915_WRITE(GEN7_MSG_CTL, temp);
		} else if (INTEL_INFO(dev)->gen >= 7) {
			u32 temp = I915_READ(HSW_NDE_RSTWRN_OPT);
			temp &= ~RESET_PCH_HANDSHAKE_ENABLE;
			I915_WRITE(HSW_NDE_RSTWRN_OPT, temp);
		}
	}

	i915_gem_init_swizzling(dev);


	init_unused_rings(dev);

	BUG_ON(!dev_priv->kernel_context);

	ret = i915_ppgtt_init_hw(dev);
	if (ret) {
		DRM_ERROR("PPGTT enable HW failed %d\n", ret);
		goto out;
	}


	for_each_engine(engine, dev_priv) {
		ret = engine->init_hw(engine);
		if (ret)
			goto out;
	}

	intel_mocs_init_l3cc_table(dev);


	if (HAS_GUC_UCODE(dev)) {
		ret = intel_guc_ucode_load(dev);
		if (ret) {
			DRM_ERROR("Failed to initialize GuC, error %d\n", ret);
			ret = -EIO;
			goto out;
		}
	}


	ret = i915_gem_set_seqno(dev, dev_priv->next_seqno+0x100);
	if (ret)
		goto out;


	for_each_engine(engine, dev_priv) {
		struct drm_i915_gem_request *req;

		req = i915_gem_request_alloc(engine, NULL);
		if (IS_ERR(req)) {
			ret = PTR_ERR(req);
			break;
		}

		if (engine->id == RCS) {
			for (j = 0; j < NUM_L3_SLICES(dev); j++) {
				ret = i915_gem_l3_remap(req, j);
				if (ret)
					goto err_request;
			}
		}

		ret = i915_ppgtt_init_ring(req);
		if (ret)
			goto err_request;

		ret = i915_gem_context_enable(req);
		if (ret)
			goto err_request;

err_request:
		i915_add_request_no_flush(req);
		if (ret) {
			DRM_ERROR("Failed to enable %s, error=%d\n",
				  engine->name, ret);
			i915_gem_cleanup_engines(dev);
			break;
		}
	}

out:
	intel_uncore_forcewake_put(dev_priv, FORCEWAKE_ALL);
	return ret;
}
