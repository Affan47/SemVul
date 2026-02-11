brw_debug_recompile_sampler_key(struct brw_context *brw,
                                const struct brw_sampler_prog_key_data *old_key,
                                const struct brw_sampler_prog_key_data *key)
{
   bool found = false;

   for (unsigned int i = 0; i < MAX_SAMPLERS; i++) {
      found |= key_debug(brw, "EXT_texture_swizzle or DEPTH_TEXTURE_MODE",
                         old_key->swizzles[i], key->swizzles[i]);
   }
   found |= key_debug(brw, "GL_CLAMP enabled on any texture unit's 1st coordinate",
                      old_key->gl_clamp_mask[0], key->gl_clamp_mask[0]);
   found |= key_debug(brw, "GL_CLAMP enabled on any texture unit's 2nd coordinate",
                      old_key->gl_clamp_mask[1], key->gl_clamp_mask[1]);
   found |= key_debug(brw, "GL_CLAMP enabled on any texture unit's 3rd coordinate",
                      old_key->gl_clamp_mask[2], key->gl_clamp_mask[2]);
   found |= key_debug(brw, "GL_MESA_ycbcr texturing\n",
                      old_key->yuvtex_mask, key->yuvtex_mask);
   found |= key_debug(brw, "GL_MESA_ycbcr UV swapping\n",
                      old_key->yuvtex_swap_mask, key->yuvtex_swap_mask);
   found |= key_debug(brw, "gather channel quirk on any texture unit",
                      old_key->gather_channel_quirk_mask, key->gather_channel_quirk_mask);

   return found;
}
