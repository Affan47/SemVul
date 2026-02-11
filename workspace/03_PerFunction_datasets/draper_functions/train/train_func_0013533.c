intel_copy_texsubimage(struct brw_context *brw,
                       struct intel_texture_image *intelImage,
                       GLint dstx, GLint dsty, GLint slice,
                       struct intel_renderbuffer *irb,
                       GLint x, GLint y, GLsizei width, GLsizei height)
{
   const GLenum internalFormat = intelImage->base.Base.InternalFormat;

   intel_prepare_render(brw);


   if (irb->Base.Base.NumSamples != 0)
      return false;


   assert(intelImage->base.Base.NumSamples == 0);

   if (!intelImage->mt || !irb || !irb->mt) {
      if (unlikely(INTEL_DEBUG & DEBUG_PERF))
	 fprintf(stderr, "%s fail %p %p (0x%08x)\n",
		 __FUNCTION__, intelImage->mt, irb, internalFormat);
      return false;
   }


   if (!intel_miptree_blit(brw,
                           irb->mt, irb->mt_level, irb->mt_layer,
                           x, y, irb->Base.Base.Name == 0,
                           intelImage->mt, intelImage->base.Base.Level,
                           intelImage->base.Base.Face + slice,
                           dstx, dsty, false,
                           width, height, GL_COPY)) {
      return false;
   }

   return true;
}
