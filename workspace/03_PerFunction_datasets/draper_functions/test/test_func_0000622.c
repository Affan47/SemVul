_mesa_texstore_z32f_x24s8(TEXSTORE_PARAMS)
{
   ASSERT(dstFormat == MESA_FORMAT_Z32_FLOAT_S8X24_UINT);
   ASSERT(srcFormat == GL_DEPTH_STENCIL ||
          srcFormat == GL_DEPTH_COMPONENT ||
          srcFormat == GL_STENCIL_INDEX);
   ASSERT(srcFormat != GL_DEPTH_STENCIL ||
          srcType == GL_FLOAT_32_UNSIGNED_INT_24_8_REV);

   if (srcFormat == GL_DEPTH_COMPONENT ||
       srcFormat == GL_STENCIL_INDEX) {
      GLint img, row;
      const GLint srcRowStride
         = _mesa_image_row_stride(srcPacking, srcWidth, srcFormat, srcType)
         / sizeof(uint64_t);


      for (img = 0; img < srcDepth; img++) {
         uint64_t *dstRow = (uint64_t *) dstSlices[img];
         const uint64_t *src
            = (const uint64_t *) _mesa_image_address(dims, srcPacking, srcAddr,
                  srcWidth, srcHeight,
                  srcFormat, srcType,
                  img, 0, 0);
         for (row = 0; row < srcHeight; row++) {


            if (srcFormat != GL_STENCIL_INDEX)
               _mesa_unpack_depth_span(ctx, srcWidth,
                                       GL_FLOAT_32_UNSIGNED_INT_24_8_REV,
                                       dstRow,
                                       ~0U, srcType, src, srcPacking);

            if (srcFormat != GL_DEPTH_COMPONENT)
               _mesa_unpack_stencil_span(ctx, srcWidth,
                                         GL_FLOAT_32_UNSIGNED_INT_24_8_REV,
                                         dstRow,
                                         srcType, src, srcPacking,
                                         ctx->_ImageTransferState);

            src += srcRowStride;
            dstRow += dstRowStride / sizeof(uint64_t);
         }
      }
   }
   return GL_TRUE;
}
