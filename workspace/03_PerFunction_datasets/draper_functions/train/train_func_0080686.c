setup_scan_request (GT68xx_Scanner * s, GT68xx_Scan_Request * scan_request)
{

  if (s->dev->model->flags & GT68XX_FLAG_MIRROR_X)
    scan_request->x0 =
      s->opt[OPT_TL_X].constraint.range->max - s->val[OPT_BR_X].w;
  else
    scan_request->x0 = s->val[OPT_TL_X].w;
  scan_request->y0 = s->val[OPT_TL_Y].w;
  scan_request->xs = s->val[OPT_BR_X].w - s->val[OPT_TL_X].w;
  scan_request->ys = s->val[OPT_BR_Y].w - s->val[OPT_TL_Y].w;

  if (s->val[OPT_FULL_SCAN].w == SANE_TRUE)
    {
      scan_request->x0 -= s->dev->model->x_offset;
      scan_request->y0 -= (s->dev->model->y_offset);
      scan_request->xs += s->dev->model->x_offset;
      scan_request->ys += s->dev->model->y_offset;
    }

  scan_request->xdpi = s->val[OPT_RESOLUTION].w;
  if (scan_request->xdpi > s->dev->model->optical_xdpi)
    scan_request->xdpi = s->dev->model->optical_xdpi;
  scan_request->ydpi = s->val[OPT_RESOLUTION].w;

  if (IS_ACTIVE (OPT_BIT_DEPTH) && !s->val[OPT_PREVIEW].w)
    scan_request->depth = s->val[OPT_BIT_DEPTH].w;
  else
    scan_request->depth = 8;

  if (strcmp (s->val[OPT_MODE].s, SANE_VALUE_SCAN_MODE_COLOR) == 0)
    scan_request->color = SANE_TRUE;
  else
    scan_request->color = SANE_FALSE;

  if (strcmp (s->val[OPT_MODE].s, SANE_VALUE_SCAN_MODE_LINEART) == 0)
    {
      SANE_Int xs =
        SANE_UNFIX (scan_request->xs) * scan_request->xdpi / MM_PER_INCH +
        0.5;

      if (xs % 8)
        {
          scan_request->xs =
            SANE_FIX ((xs - (xs % 8)) * MM_PER_INCH / scan_request->xdpi);
          DBG (5, "setup_scan_request: lineart mode, %d pixels %% 8 = %d\n",
               xs, xs % 8);
        }
    }

  scan_request->calculate = SANE_FALSE;
  scan_request->lamp = SANE_TRUE;
  scan_request->mbs = SANE_FALSE;

  if (strcmp (s->val[OPT_SOURCE].s, "Transparency Adapter") == 0)
    scan_request->use_ta = SANE_TRUE;
  else
    scan_request->use_ta = SANE_FALSE;

  return SANE_STATUS_GOOD;
}
