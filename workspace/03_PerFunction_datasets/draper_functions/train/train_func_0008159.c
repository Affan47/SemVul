effective_func(GLenum func, bool src_alpha_is_one)
{
   if (src_alpha_is_one) {
      if (func == GL_SRC_ALPHA)
	 return GL_ONE;
      if (func == GL_ONE_MINUS_SRC_ALPHA)
	 return GL_ZERO;
   }

   return func;
}
