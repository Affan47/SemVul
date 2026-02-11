gxineinfo_update (const GSList *objs)
{
  foreach_glist (objs, objs)
    if (GTK_IS_GXINE_INFO (objs->data))
    {
      gxineinfo_private_t *priv = GET_PRIVATE (objs->data);
      if (priv->update)
	priv->update (objs->data);
    }
}
