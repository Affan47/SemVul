_mesa_MapGrid2f( GLint un, GLfloat u1, GLfloat u2,
                 GLint vn, GLfloat v1, GLfloat v2 )
{
   GET_CURRENT_CONTEXT(ctx);

   if (un<1) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glMapGrid2f(un)" );
      return;
   }
   if (vn<1) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glMapGrid2f(vn)" );
      return;
   }

   FLUSH_VERTICES(ctx, _NEW_EVAL);
   ctx->Eval.MapGrid2un = un;
   ctx->Eval.MapGrid2u1 = u1;
   ctx->Eval.MapGrid2u2 = u2;
   ctx->Eval.MapGrid2du = (u2 - u1) / (GLfloat) un;
   ctx->Eval.MapGrid2vn = vn;
   ctx->Eval.MapGrid2v1 = v1;
   ctx->Eval.MapGrid2v2 = v2;
   ctx->Eval.MapGrid2dv = (v2 - v1) / (GLfloat) vn;
}
