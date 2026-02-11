chatnet_remove(CHATNET_REC *chatnet)
{
	g_return_if_fail(IS_CHATNET(chatnet));

	signal_emit("chatnet removed", 1, chatnet);

	chatnet_config_remove(chatnet);
	chatnet_destroy(chatnet);
}
