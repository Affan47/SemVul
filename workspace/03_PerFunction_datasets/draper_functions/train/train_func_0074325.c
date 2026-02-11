mgopengl_ctxselect( mgcontext *ctx )
{
  if(ctx == NULL || ctx->devno != MGD_OPENGL) {
    return mg_ctxselect(ctx);
  }

  _mgc = ctx;
  if(_mgopenglc->win) {
#ifdef GLUT
    if(_mgopenglc->win <= 0)
      mgopengl_choosewin();
    if(_mgopenglc->win > 0)
      glutSetWindow(_mgopenglc->win);

#else
    if(_mgopenglc->GLXdisplay != NULL) {
      _mgopenglc->win = _mgopenglc->winids[ _mgc->opts & MGO_DOUBLEBUFFER ? DBL : SGL ];
      _mgopenglc->curctx = _mgopenglc->cam_ctx[ _mgc->opts & MGO_DOUBLEBUFFER ? DBL : SGL ];
      if(_mgopenglc->win > 0)
        glXMakeCurrent( (Display *)_mgopenglc->GLXdisplay,
			(Window) _mgopenglc->win,
			_mgopenglc->curctx);
    }
#endif
  }
  return 0;
}
