choose_copy_pv_func(  struct gl_context *ctx, GLuint edst, GLuint esrc )
{
   struct tnl_clipspace *vtx = GET_VERTEX_STATE(ctx);
   GLboolean unfilled = (ctx->Polygon.FrontMode != GL_FILL ||
                         ctx->Polygon.BackMode != GL_FILL);

   GLboolean twosided = ctx->Light.Enabled && ctx->Light.Model.TwoSide;

   if (vtx->need_extras && (twosided || unfilled)) {
      vtx->copy_pv = _tnl_generic_copy_pv_extras;
   } else {
      vtx->copy_pv = _tnl_generic_copy_pv;
   }

   vtx->copy_pv( ctx, edst, esrc );
}
