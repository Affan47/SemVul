radeon_bo_unref(struct radeon_bo **bo)
{
	struct ttm_buffer_object *tbo;
	struct radeon_device *rdev;

	if ((*bo) == NULL)
		return;
	rdev = (*bo)->rdev;
	tbo = &((*bo)->tbo);
	ttm_bo_unref(&tbo);
	if (tbo == NULL)
		*bo = NULL;
}
