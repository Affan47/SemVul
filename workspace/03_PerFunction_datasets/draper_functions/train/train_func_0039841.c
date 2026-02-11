mgopengl_newcontext( mgopenglcontext *ctx )
{
  mg_newcontext(&(ctx->mgctx));
  ctx->mgctx.devfuncs = &mgopenglfuncs;
  ctx->mgctx.devno = MGD_OPENGL;
  ctx->mgctx.astk->ap_seq = 0;
  ctx->mgctx.astk->mat_seq = 0;
  ctx->mgctx.astk->light_seq = 0;
  ctx->mgctx.zfnudge = 40.e-6;
  ctx->born = 0;
  ctx->win = 0;
  ctx->winids[SGL] = ctx->winids[DBL] = 0;
  {
    mgcontext *oldmgc = _mgc;
    _mgc = (mgcontext *)ctx;
    D4F_OFF();
    N3F_NOEVERT();
    _mgc = oldmgc;
  }
  ctx->lmcolor = GL_DIFFUSE;
  ctx->tevbound = 0;
  ctx->curtex = NULL;
  VVINIT(ctx->room, char, 180);
#ifndef GLUT
  ctx->GLXdisplay = NULL;
  ctx->cam_ctx[SGL] = ctx->cam_ctx[DBL] = 0;
  ctx->curctx = 0;
#endif
  ctx->should_lighting = ctx->is_lighting = 0;
  ctx->dither = 1;
  ctx->bgimagefile = NULL;


  ctx->n_light_lists = 0;
  ctx->light_lists = NULL;
  ctx->n_texture_lists = 0;
  ctx->texture_lists = NULL;
  ctx->n_translucent_lists = 0;
  ctx->translucent_lists = NULL;
  ctx->translucent_seq = 0;

  return ctx;
}
