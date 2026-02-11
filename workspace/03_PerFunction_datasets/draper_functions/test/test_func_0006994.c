make_drawing_gcs (XlwMenuWidget mw)
{
  XGCValues xgcv;
  float scale;
  XtGCMask mask = GCForeground | GCBackground;

#ifdef HAVE_X_I18N
  if (!mw->menu.fontSet && mw->menu.font)
    {
      xgcv.font = mw->menu.font->fid;
      mask |= GCFont;
    }
#else
  if (mw->menu.font)
    {
      xgcv.font = mw->menu.font->fid;
      mask |= GCFont;
    }
#endif
  xgcv.foreground = mw->menu.foreground;
  xgcv.background = mw->core.background_pixel;
  mw->menu.foreground_gc = XtGetGC ((Widget)mw, mask, &xgcv);

  xgcv.foreground = mw->menu.button_foreground;
  mw->menu.button_gc = XtGetGC ((Widget)mw, mask, &xgcv);

  xgcv.background = mw->core.background_pixel;

#define BRIGHTNESS(color) (((color) & 0xff) + (((color) >> 8) & 0xff) + (((color) >> 16) & 0xff))


  mw->menu.disabled_foreground = mw->menu.foreground;
  if (BRIGHTNESS(mw->menu.foreground) < BRIGHTNESS(mw->core.background_pixel))
    scale = 2.3;
  else
    scale = 0.55;

  x_alloc_lighter_color_for_widget ((Widget) mw, XtDisplay ((Widget) mw),
				    mw->core.colormap,
				    &mw->menu.disabled_foreground,
				    scale,
				    0x8000);

  if (mw->menu.foreground == mw->menu.disabled_foreground
      || mw->core.background_pixel == mw->menu.disabled_foreground)
    {

      xgcv.foreground = mw->menu.foreground;
      xgcv.fill_style = FillStippled;
      xgcv.stipple = mw->menu.gray_pixmap;
      mw->menu.disabled_gc = XtGetGC ((Widget)mw, mask
				      | GCFillStyle | GCStipple, &xgcv);
    }
  else
    {

      xgcv.foreground = mw->menu.disabled_foreground;
      mw->menu.disabled_gc = XtGetGC ((Widget)mw, mask, &xgcv);
    }

  xgcv.foreground = mw->menu.button_foreground;
  xgcv.background = mw->core.background_pixel;
  xgcv.fill_style = FillStippled;
  xgcv.stipple = mw->menu.gray_pixmap;
  mw->menu.inactive_button_gc = XtGetGC ((Widget)mw, mask
					 | GCFillStyle | GCStipple, &xgcv);

  xgcv.foreground = mw->core.background_pixel;
  xgcv.background = mw->menu.foreground;
  mw->menu.background_gc = XtGetGC ((Widget)mw, mask, &xgcv);
}
