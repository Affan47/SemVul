bufferevent_remove_from_rate_limit_group_internal_(struct bufferevent *bev,
    int unsuspend)
{
	struct bufferevent_private *bevp =
	    EVUTIL_UPCAST(bev, struct bufferevent_private, bev);
	BEV_LOCK(bev);
	if (bevp->rate_limiting && bevp->rate_limiting->group) {
		struct bufferevent_rate_limit_group *g =
		    bevp->rate_limiting->group;
		LOCK_GROUP(g);
		bevp->rate_limiting->group = NULL;
		--g->n_members;
		LIST_REMOVE(bevp, rate_limiting->next_in_group);
		UNLOCK_GROUP(g);
	}
	if (unsuspend) {
		bufferevent_unsuspend_read_(bev, BEV_SUSPEND_BW_GROUP);
		bufferevent_unsuspend_write_(bev, BEV_SUSPEND_BW_GROUP);
	}
	BEV_UNLOCK(bev);
	return 0;
}
