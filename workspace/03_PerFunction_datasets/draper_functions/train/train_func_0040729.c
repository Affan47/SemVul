intel_batchbuffer_reset(struct intel_context *intel)
{
   if (intel->batch.last_bo != NULL) {
      drm_intel_bo_unreference(intel->batch.last_bo);
      intel->batch.last_bo = NULL;
   }
   intel->batch.last_bo = intel->batch.bo;

   intel->batch.bo = drm_intel_bo_alloc(intel->bufmgr, "batchbuffer",
					intel->maxBatchSize, 4096);

   intel->batch.reserved_space = BATCH_RESERVED;
   intel->batch.used = 0;
}
