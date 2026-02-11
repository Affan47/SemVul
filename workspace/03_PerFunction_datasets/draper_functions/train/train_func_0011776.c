up_qos_finalize (GObject *object)
{
	UpQos *qos;
	guint i;

	g_return_if_fail (object != NULL);
	g_return_if_fail (UP_IS_QOS (object));

	qos = UP_QOS (object);
	qos->priv = UP_QOS_GET_PRIVATE (qos);


	for (i=0; i<UP_QOS_KIND_LAST; i++) {
		if (qos->priv->fd[i] > 0)
			close (qos->priv->fd[i]);
	}
	g_ptr_array_unref (qos->priv->data);
	g_object_unref (qos->priv->proxy);

	g_object_unref (qos->priv->polkit);

	G_OBJECT_CLASS (up_qos_parent_class)->finalize (object);
}
