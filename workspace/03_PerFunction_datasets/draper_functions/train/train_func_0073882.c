setup(void) {
	 CHECK(isc_mem_create(0, 0, &mctx));
	 CHECK(isc_timermgr_create(mctx, &timer_manager));
	 CHECK(isc_taskmgr_create(mctx, 1, 0, &task_manager));
	 CHECK(isc_socketmgr_create(mctx, &socket_manager));
	 CHECK(dns_dispatchmgr_create(mctx, NULL, &dispatch_manager));
	 CHECK(dns_view_create(mctx, dns_rdataclass_in, "testview", &view));
	 setup_create_dispatch_v4();
}
