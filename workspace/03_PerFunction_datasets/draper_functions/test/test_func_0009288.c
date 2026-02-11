amdgpu_irq_disable_all(struct amdgpu_device *adev)
{
	unsigned long irqflags;
	unsigned i, j;
	int r;

	spin_lock_irqsave(&adev->irq.lock, irqflags);
	for (i = 0; i < AMDGPU_MAX_IRQ_SRC_ID; ++i) {
		struct amdgpu_irq_src *src = adev->irq.sources[i];

		if (!src || !src->funcs->set || !src->num_types)
			continue;

		for (j = 0; j < src->num_types; ++j) {
			atomic_set(&src->enabled_types[j], 0);
			r = src->funcs->set(adev, src, j,
					    AMDGPU_IRQ_STATE_DISABLE);
			if (r)
				DRM_ERROR("error disabling interrupt (%d)\n",
					  r);
		}
	}
	spin_unlock_irqrestore(&adev->irq.lock, irqflags);
}
