dsm_notify_put(int nid, string blockId) {

		ostringstream outs;
		outs << "dsm_put " << nid << " " << blockId;
		dsm_notify(outs.str());
	}
