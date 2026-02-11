visu_box_setMargin(VisuBox *box, gfloat margin, gboolean emit)
{
  g_return_val_if_fail(VISU_IS_BOX(box), FALSE);

  if (margin < 0.f || margin == box->priv->margin)
    return FALSE;

  box->priv->margin = margin;

  if (box->priv->cell[0] != G_MAXFLOAT && box->priv->margin != G_MAXFLOAT && emit)
    {
      DBG_fprintf(stderr, "Visu Box: emit SizeChanged.\n");
      g_signal_emit(box, visu_box_signals[SIZE_CHANGED_SIGNAL],
                    0, box->priv->extens[1] + box->priv->margin, NULL);
      DBG_fprintf(stderr, "Visu Box: emission done (SizeChanged).\n");
    }

  return TRUE;
}
