_mesa_set_depth_range(struct gl_context *ctx, unsigned idx,
                      GLclampd nearval, GLclampd farval)
{
   set_depth_range_no_notify(ctx, idx, nearval, farval);

   if (ctx->Driver.DepthRange)
      ctx->Driver.DepthRange(ctx);
}
