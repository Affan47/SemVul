Scheduler(int block)
{


    int returnValue;
    int netin, netout, netex, ttyin, ttyout;


    netout = ring_full_count(&netoring) &&
	    (flushline ||
		(my_want_state_is_wont(TELOPT_LINEMODE)
#ifdef	KLUDGELINEMODE
			&& (!kludgelinemode || my_want_state_is_do(TELOPT_SGA))
#endif
		) ||
			my_want_state_is_will(TELOPT_BINARY));
    ttyout = ring_full_count(&ttyoring);

    ttyin = ring_empty_count(&ttyiring);

    netin = !ISend && ring_empty_count(&netiring);

    netex = !SYNCHing;


    if (scheduler_lockout_tty) {
        ttyin = ttyout = 0;
    }


    returnValue = process_rings(netin, netout, netex, ttyin, ttyout, !block);


    if (ring_full_count(&ttyiring)) {
	    returnValue |= telsnd();
    }

    if (ring_full_count(&netiring)) {
	returnValue |= telrcv();
    }
    return returnValue;
}
