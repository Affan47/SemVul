iscsit_get_np(
	struct sockaddr_storage *sockaddr,
	int network_transport)
{
	struct iscsi_np *np;
	bool match;

	list_for_each_entry(np, &g_np_list, np_list) {
		spin_lock_bh(&np->np_thread_lock);
		if (np->np_thread_state != ISCSI_NP_THREAD_ACTIVE) {
			spin_unlock_bh(&np->np_thread_lock);
			continue;
		}

		match = iscsit_check_np_match(sockaddr, np, network_transport);
		if (match) {


			np->np_exports++;
			spin_unlock_bh(&np->np_thread_lock);
			return np;
		}
		spin_unlock_bh(&np->np_thread_lock);
	}

	return NULL;
}
