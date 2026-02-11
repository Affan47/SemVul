check_flush( struct copy_context *copy )
{
   GLenum mode = copy->dstprim[copy->dstprim_nr].mode;

   if (GL_TRIANGLE_STRIP == mode &&
       copy->dstelt_nr & 1) {
       return GL_FALSE;
   }

   if (copy->dstbuf_nr + 4 > copy->dstbuf_size)
      return GL_TRUE;

   if (copy->dstelt_nr + 4 > copy->dstelt_size)
      return GL_TRUE;

   return GL_FALSE;
}
