l2tp_tunnel_start(struct l2tp_conn_t *conn,
			     triton_event_func start_func,
			     void *start_param)
{
	if (triton_context_register(&conn->ctx, NULL) < 0) {
		log_error("l2tp: impossible to start new tunnel:"
			  " context registration failed\n");
		goto err;
	}
	triton_md_register_handler(&conn->ctx, &conn->hnd);
	if (triton_md_enable_handler(&conn->hnd, MD_MODE_READ) < 0) {
		log_error("l2tp: impossible to start new tunnel:"
			  " enabling handler failed\n");
		goto err_ctx;
	}
	triton_context_wakeup(&conn->ctx);
	if (triton_timer_add(&conn->ctx, &conn->timeout_timer, 0) < 0) {
		log_error("l2tp: impossible to start new tunnel:"
			  " setting tunnel establishment timer failed\n");
		goto err_ctx_md;
	}
	if (triton_context_call(&conn->ctx, start_func, start_param) < 0) {
		log_error("l2tp: impossible to start new tunnel:"
			  " call to tunnel context failed\n");
		goto err_ctx_md_timer;
	}

	return 0;

err_ctx_md_timer:
	triton_timer_del(&conn->timeout_timer);
err_ctx_md:
	triton_md_unregister_handler(&conn->hnd, 0);
err_ctx:
	triton_context_unregister(&conn->ctx);
err:
	return -1;
}
