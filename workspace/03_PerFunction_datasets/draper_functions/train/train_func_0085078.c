unity_webapps_context_destroy (UnityWebappsContext *context, gboolean user_abandoned)
{
  g_return_if_fail (context != NULL);
  g_return_if_fail (UNITY_WEBAPPS_IS_CONTEXT (context));

  context->priv->user_abandoned = user_abandoned;
  g_object_unref (G_OBJECT (context));
}
