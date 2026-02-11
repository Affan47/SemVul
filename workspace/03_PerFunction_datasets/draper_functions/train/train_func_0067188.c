nv10_bo_put_tile_region(struct drm_device *dev, struct nouveau_drm_tile *tile,
			struct fence *fence)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (tile) {
		spin_lock(&drm->tile.lock);
		tile->fence = (struct nouveau_fence *)fence_get(fence);
		tile->used = false;
		spin_unlock(&drm->tile.lock);
	}
}
