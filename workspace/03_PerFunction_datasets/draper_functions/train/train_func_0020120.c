reload_vrrp_thread(thread_t * thread)
{

	SET_RELOAD;


	signal_reset();
	signal_handler_destroy();


	vrrp_dispatcher_release(vrrp_data);
	kernel_netlink_close();
	thread_destroy_master(master);
	master = thread_make_master();
	free_global_data(global_data);
	free_interface_queue();
	free_vrrp_buffer();
	gratuitous_arp_close();
	ndisc_close();

#ifdef _WITH_LVS_
	if (vrrp_ipvs_needed()) {

		ipvs_stop();
	}
#endif


	old_vrrp_data = vrrp_data;
	vrrp_data = NULL;


	mem_allocated = 0;
	vrrp_signal_init();
	signal_set(SIGCHLD, thread_child_handler, master);
	start_vrrp();


	free_vrrp_data(old_vrrp_data);
	UNSET_RELOAD;

	return 0;
}
