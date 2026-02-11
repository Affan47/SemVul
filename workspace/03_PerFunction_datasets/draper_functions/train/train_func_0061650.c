smsdvb_module_exit(void)
{
	smscore_unregister_hotplug(smsdvb_hotplug);

	kmutex_lock(&g_smsdvb_clientslock);

	while (!list_empty(&g_smsdvb_clients))
		smsdvb_unregister_client((struct smsdvb_client_t *)g_smsdvb_clients.next);

	smsdvb_debugfs_unregister();

	kmutex_unlock(&g_smsdvb_clientslock);
}
