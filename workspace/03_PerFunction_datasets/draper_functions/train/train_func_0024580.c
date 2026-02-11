mx_style_stylable_cache_free (MxStylableCache *cache)
{


  while (cache->styles)
    {
      MxStyle *style = cache->styles->data;
      MxStylePrivate *priv = style->priv;

      g_object_weak_unref (G_OBJECT (style),
                           mx_style_cache_weak_ref_cb,
                           cache);
      priv->alive_stylables --;

      MX_NOTE (STYLE_CACHE, "(%p) Alive stylables: %d",
               style, priv->alive_stylables);

      cache->styles = g_list_delete_link (cache->styles, cache->styles);
    }

  g_free (cache->string);
  g_slice_free (MxStylableCache, cache);
}
