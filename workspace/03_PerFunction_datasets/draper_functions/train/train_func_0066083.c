_mesa_IsList(GLuint list)
{
   GET_CURRENT_CONTEXT(ctx);
   FLUSH_VERTICES(ctx, 0);
   ASSERT_OUTSIDE_BEGIN_END_WITH_RETVAL(ctx, GL_FALSE);
   return islist(ctx, list);
}
