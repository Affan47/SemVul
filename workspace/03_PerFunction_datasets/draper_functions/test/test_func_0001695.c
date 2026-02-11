vrrp_log_tracked_down(list l)
{
	element e;
	tracked_if_t *tip;

	for (e = LIST_HEAD(l); e; ELEMENT_NEXT(e)) {
		tip = ELEMENT_DATA(e);
		if (!IF_ISUP(tip->ifp))
			log_message(LOG_INFO, "Kernel is reporting: interface %s DOWN",
			       IF_NAME(tip->ifp));
	}
}
