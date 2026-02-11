ap_session_init(struct ap_session *ses)
{
	memset(ses, 0, sizeof(*ses));
	INIT_LIST_HEAD(&ses->pd_list);
	ses->ifindex = -1;
}
