i810_freelist_put(struct drm_device *dev, struct drm_buf *buf)
{
	drm_i810_buf_priv_t *buf_priv = buf->dev_private;
	int used;


	used = cmpxchg(buf_priv->in_use, I810_BUF_CLIENT, I810_BUF_FREE);
	if (used != I810_BUF_CLIENT) {
		DRM_ERROR("Freeing buffer thats not in use : %d\n", buf->idx);
		return -EINVAL;
	}

	return 0;
}
