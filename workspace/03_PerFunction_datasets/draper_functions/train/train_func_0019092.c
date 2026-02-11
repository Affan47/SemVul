intel_process_dri2_buffer(struct intel_context *intel,
			  __DRIdrawable *drawable,
			  __DRIbuffer *buffer,
			  struct intel_renderbuffer *rb,
			  const char *buffer_name)
{
   struct intel_region *region = NULL;

   if (!rb)
      return;


   if (rb->mt &&
       rb->mt->region &&
       rb->mt->region->name == buffer->name &&
       rb->mt->region->name != 0)
      return;

   if (unlikely(INTEL_DEBUG & DEBUG_DRI)) {
      fprintf(stderr,
	      "attaching buffer %d, at %d, cpp %d, pitch %d, fd %d\n",
	      buffer->name, buffer->attachment,
	      buffer->cpp, buffer->pitch, buffer->fd);
   }

   intel_miptree_release(&rb->mt);
   if (buffer->name != 0) {
      region = intel_region_alloc_for_handle(intel->intelScreen,
                                             buffer->cpp,
                                             drawable->w,
                                             drawable->h,
                                             buffer->pitch,
                                             buffer->name,
                                             buffer_name);
   } else {
      region = intel_region_alloc_for_fd(intel->intelScreen,
                                         buffer->cpp,
                                         drawable->w,
                                         drawable->h,
                                         buffer->pitch,
                                         0,
                                         buffer->fd,
                                         buffer_name);
   }
   if (!region)
      return;

   rb->mt = intel_miptree_create_for_dri2_buffer(intel,
                                                 buffer->attachment,
                                                 intel_rb_format(rb),
                                                 region);
   intel_region_release(&region);
}
