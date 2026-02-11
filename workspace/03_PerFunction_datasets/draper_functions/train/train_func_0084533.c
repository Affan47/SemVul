peerMonitorCompleted(PeerMonitor * pm)
{
    int state = PEER_ALIVE;
    peer *p = pm->peer;
    storeClientUnregister(pm->running.sc, pm->running.e, pm);
    storeUnlockObject(pm->running.e);
    requestUnlink(pm->running.req);
    if (pm->running.timeout_set) {
	eventDelete(peerMonitorTimeout, pm);
	pm->running.timeout_set = 0;
    }
    if (!cbdataValid(pm->peer)) {
	cbdataFree(pm);
	return;
    }

    if (pm->running.status != HTTP_OK) {
	debug(DBG, 1) ("peerMonitor %s: Failed, status != 200 (%d)\n",
	    p->name, pm->running.status);
	state = PEER_DEAD;
    } else if (pm->running.size < p->monitor.min) {
	debug(DBG, 1) ("peerMonitor %s: Failed, reply size %d < min %d\n",
	    p->name, pm->running.size, p->monitor.min);
	state = PEER_DEAD;
    } else if (pm->running.size > p->monitor.max && p->monitor.max > 0) {
	debug(DBG, 1) ("peerMonitor %s: Failed, reply size %d > max %d\n",
	    p->name, pm->running.size, p->monitor.max);
	state = PEER_DEAD;
    } else {
	debug(DBG, 2) ("peerMonitor %s: OK\n", p->name);
    }
    p->monitor.state = state;
    if (state != p->stats.logged_state) {
	switch (state) {
	case PEER_ALIVE:
	    debug(DBG, 1) ("Detected REVIVED %s: %s\n",
		neighborTypeStr(p), p->name);
	    peerClearRR();
	    break;
	case PEER_DEAD:
	    debug(DBG, 1) ("Detected DEAD %s: %s\n",
		neighborTypeStr(p), p->name);
	    break;
	}
	p->stats.logged_state = state;
    }
    memset(&pm->running, 0, sizeof(pm->running));
    eventAdd(pm->name, peerMonitorRequest, pm, (double) (pm->last_probe + pm->peer->monitor.interval - current_dtime), 1);
}
