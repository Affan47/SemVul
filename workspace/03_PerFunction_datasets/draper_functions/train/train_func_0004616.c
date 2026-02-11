intel_get_current_max(struct intel_context *intel)
{
   GLuint ret;

   if (intel->intelScreen->no_vbo) {
      ret = intel_batchbuffer_space(intel);
      ret = ret <= INTEL_NO_VBO_STATE_RESERVED ? 0 : ret - INTEL_NO_VBO_STATE_RESERVED;
   } else
      ret = (INTEL_VB_SIZE - intel->prim.current_offset);

   return ret / (intel->vertex_size * 4);
}
