sourceact_handler(pst_packetsource *src, int action,
										  int flags) {
	if (action == SOURCEACT_ADDSOURCE) {

		SendAllSource(src, 0);
	} else if (action == SOURCEACT_DELSOURCE) {

		SendAllSource(src, 1);
	} else if (action == SOURCEACT_HOPENABLE || action == SOURCEACT_HOPDISABLE ||
			   action == SOURCEACT_CHVECTOR) {

		SendAllChannels(src);
	}
}
