_mesa_install_exec_vtxfmt(struct gl_context *ctx, const GLvertexformat *vfmt)
{
   install_vtxfmt(ctx, ctx->Exec, vfmt);
   if (ctx->BeginEnd)
      install_vtxfmt(ctx, ctx->BeginEnd, vfmt);
}
