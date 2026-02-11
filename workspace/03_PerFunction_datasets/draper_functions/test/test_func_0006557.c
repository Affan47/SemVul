art_render_invoke_callbacks (ArtRender *render, art_u8 *dest, int y)
{
  ArtRenderPriv *priv = (ArtRenderPriv *)render;
  int i;

  for (i = 0; i < priv->n_callbacks; i++)
    {
      ArtRenderCallback *callback;

      callback = priv->callbacks[i];
      callback->render (callback, render, dest, y);
    }
}
