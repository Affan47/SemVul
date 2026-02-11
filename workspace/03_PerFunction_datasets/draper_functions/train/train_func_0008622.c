i830BlendEquationSeparate(struct gl_context * ctx, GLenum modeRGB, GLenum modeA)
{
   DBG("%s -> %s, %s\n", __FUNCTION__,
       _mesa_lookup_enum_by_nr(modeRGB),
       _mesa_lookup_enum_by_nr(modeA));

   (void) modeRGB;
   (void) modeA;
   i830_set_blend_state(ctx);
}
