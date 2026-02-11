_libnm_glib_ctx_free (libnm_glib_ctx *ctx)
{
	g_return_if_fail (ctx != NULL);

	if (ctx->check == 0xDD)
	{
		fprintf (stderr, "%s: context %p already freed!\n", __func__, ctx);
		return;
	}

	if (ctx->g_main_ctx)
		g_main_context_unref (ctx->g_main_ctx);
	if (ctx->g_main_loop)
		g_main_loop_unref (ctx->g_main_loop);

	if (ctx->dbus_con)
	{
		dbus_connection_close (ctx->dbus_con);
		dbus_connection_unref (ctx->dbus_con);
		ctx->dbus_con = NULL;
	}

	if (ctx->callbacks_lock)
		g_mutex_free (ctx->callbacks_lock);

	g_slist_foreach (ctx->callbacks, (GFunc)g_free, NULL);
	g_slist_free (ctx->callbacks);

	if (ctx->thread)
		g_thread_join (ctx->thread);

	memset (ctx, 0, sizeof (libnm_glib_ctx));
	memset (&(ctx->check), 0xDD, sizeof (ctx->check));
	g_free (ctx);
}
