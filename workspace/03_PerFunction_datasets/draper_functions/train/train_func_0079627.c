clutter_stage_invoke_paint_callback (ClutterStage *stage)
{
  if (stage->priv->paint_callback != NULL)
    stage->priv->paint_callback (stage, stage->priv->paint_data);
}
