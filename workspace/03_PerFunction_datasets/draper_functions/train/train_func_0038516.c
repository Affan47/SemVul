intel_batchbuffer_reset_to_saved(struct brw_context *brw)
{
   drm_intel_gem_bo_clear_relocs(brw->batch.bo, brw->batch.saved.reloc_count);

   brw->batch.used = brw->batch.saved.used;
   if (brw->batch.used == 0)
      brw->batch.ring = UNKNOWN_RING;


   intel_batchbuffer_clear_cache(brw);
}
