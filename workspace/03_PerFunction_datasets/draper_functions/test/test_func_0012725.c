check_driver()
{
#if CLICK_LINUXMODULE
    assert(!in_interrupt());
#endif

    lock_master();
    _stopper = 0;
    bool any_active = false;

    for (Router *r = _routers; r; ) {
	Router *next_router = r->_next_router;
	if (r->runcount() <= 0 && r->_running >= Router::RUNNING_BACKGROUND) {
	    Element *dm = (Element *)(r->attachment("Script"));
	    if (dm) {
		int max = 1000;
		while (HandlerCall::call_write(dm, "step", "router", ErrorHandler::default_handler()) == 0
		       && r->runcount() <= 0 && --max >= 0)
		    ;
	    }
	    if (r->runcount() <= 0 && r->_running >= Router::RUNNING_BACKGROUND) {
		kill_router(r);
		goto next;
	    }
	}
	if (r->_running == Router::RUNNING_ACTIVE)
	    any_active = true;
    next:
	r = next_router;
    }

    if (!any_active)
	_stopper = 1;
    unlock_master();
    return any_active;
}
