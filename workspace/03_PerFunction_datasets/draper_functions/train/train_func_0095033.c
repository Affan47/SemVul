run_interpreter(char raise, enum error e,
		Var * result, int is_fg, int do_db_tracebacks)


{
    enum outcome ret;
    Var args;

    setup_task_execution_limits(is_fg ? server_int_option("fg_seconds",
						      DEFAULT_FG_SECONDS)
				: server_int_option("bg_seconds",
						    DEFAULT_BG_SECONDS),
				is_fg ? server_int_option("fg_ticks",
							DEFAULT_FG_TICKS)
				: server_int_option("bg_ticks",
						    DEFAULT_BG_TICKS));


    handler_verb_args = zero;
    handler_verb_name = 0;
    interpreter_is_running = 1;
    ret = run(raise, e, result);
    interpreter_is_running = 0;
    args = handler_verb_args;

    cancel_timer(task_alarm_id);
    task_timed_out = 0;

    if (ret == OUTCOME_ABORTED && handler_verb_name) {
	db_verb_handle h;
	enum outcome hret;
	Var handled, traceback;
	int i;

	h = db_find_callable_verb(SYSTEM_OBJECT, handler_verb_name);
	if (do_db_tracebacks && h.ptr) {
	    hret = do_server_verb_task(SYSTEM_OBJECT, handler_verb_name,
				       var_ref(args), h,
				       activ_stack[0].player, "", &handled,
				       0);
	    if ((hret == OUTCOME_DONE && is_true(handled))
		|| hret == OUTCOME_BLOCKED) {

		free_var(args);
		return OUTCOME_ABORTED;
	    }
	}
	i = args.v.list[0].v.num;
	traceback = args.v.list[i];
	for (i = 1; i <= traceback.v.list[0].v.num; i++)
	    notify(activ_stack[0].player, traceback.v.list[i].v.str);
    }
    free_var(args);
    return ret;
}
