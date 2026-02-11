_on_file_loaded (FrogrFileLoader *loader, FrogrPicture *picture, FrogrController *self)
{
  FrogrControllerPrivate *priv = NULL;
  FrogrModel *model = NULL;

  g_return_if_fail (FROGR_IS_CONTROLLER (self));
  g_return_if_fail (FROGR_IS_PICTURE (picture));

  priv = FROGR_CONTROLLER_GET_PRIVATE (self);

  model = frogr_main_view_get_model (priv->mainview);
  frogr_model_add_picture (model, picture);
}
