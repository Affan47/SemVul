klp_disable_patch(struct klp_patch *patch)
{
	int ret;

	mutex_lock(&klp_mutex);

	if (!klp_is_patch_registered(patch)) {
		ret = -EINVAL;
		goto err;
	}

	if (patch->state == KLP_DISABLED) {
		ret = -EINVAL;
		goto err;
	}

	ret = __klp_disable_patch(patch);

err:
	mutex_unlock(&klp_mutex);
	return ret;
}
