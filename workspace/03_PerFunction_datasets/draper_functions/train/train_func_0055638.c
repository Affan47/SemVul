i915_l3_write(struct file *filp, struct kobject *kobj,
	      struct bin_attribute *attr, char *buf,
	      loff_t offset, size_t count)
{
	struct device *dev = kobj_to_dev(kobj);
	struct drm_minor *dminor = dev_to_drm_minor(dev);
	struct drm_device *drm_dev = dminor->dev;
	struct drm_i915_private *dev_priv = drm_dev->dev_private;
	struct intel_context *ctx;
	u32 *temp = NULL;
	int slice = (int)(uintptr_t)attr->private;
	int ret;

	if (!HAS_HW_CONTEXTS(drm_dev))
		return -ENXIO;

	ret = l3_access_valid(drm_dev, offset);
	if (ret)
		return ret;

	ret = i915_mutex_lock_interruptible(drm_dev);
	if (ret)
		return ret;

	if (!dev_priv->l3_parity.remap_info[slice]) {
		temp = kzalloc(GEN7_L3LOG_SIZE, GFP_KERNEL);
		if (!temp) {
			mutex_unlock(&drm_dev->struct_mutex);
			return -ENOMEM;
		}
	}

	ret = i915_gpu_idle(drm_dev);
	if (ret) {
		kfree(temp);
		mutex_unlock(&drm_dev->struct_mutex);
		return ret;
	}


	if (temp)
		dev_priv->l3_parity.remap_info[slice] = temp;

	memcpy(dev_priv->l3_parity.remap_info[slice] + (offset/4), buf, count);


	list_for_each_entry(ctx, &dev_priv->context_list, link)
		ctx->remap_slice |= (1<<slice);

	mutex_unlock(&drm_dev->struct_mutex);

	return count;
}
