copy_array_to_vbo_array(struct brw_context *brw,
			struct brw_vertex_element *element,
			int min, int max,
			struct brw_vertex_buffer *buffer,
			GLuint dst_stride)
{
   const int src_stride = element->glarray->StrideB;


   if (src_stride == 0) {
      intel_upload_data(brw, element->glarray->Ptr,
                        element->glarray->_ElementSize,
                        element->glarray->_ElementSize,
			&buffer->bo, &buffer->offset);

      buffer->stride = 0;
      return;
   }

   const unsigned char *src = element->glarray->Ptr + min * src_stride;
   int count = max - min + 1;
   GLuint size = count * dst_stride;

   if (dst_stride == src_stride) {
      intel_upload_data(brw, src, size, dst_stride,
			&buffer->bo, &buffer->offset);
   } else {
      char * const map = intel_upload_map(brw, size, dst_stride);
      char *dst = map;

      while (count--) {
	 memcpy(dst, src, dst_stride);
	 src += src_stride;
	 dst += dst_stride;
      }
      intel_upload_unmap(brw, map, size, dst_stride,
			 &buffer->bo, &buffer->offset);
   }
   buffer->stride = dst_stride;
}
