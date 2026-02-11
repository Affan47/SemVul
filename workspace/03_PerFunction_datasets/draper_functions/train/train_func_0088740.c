gbm_bo_destroy(struct gbm_bo *bo)
{
   if (bo->destroy_user_data)
      bo->destroy_user_data(bo, bo->user_data);

   bo->gbm->bo_destroy(bo);
}
