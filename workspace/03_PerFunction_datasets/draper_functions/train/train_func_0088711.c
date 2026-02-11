gm_net_close_thread(GmNet *net) {
	if (net->priv->thread != 0) {
		pthread_kill(net->priv->thread, SIGKILL);

		if (net->priv->thread_info->idle_id) {
			g_source_remove(net->priv->thread_info->idle_id);
		}

		gm_net_free_thread_info(net);
	}
}
