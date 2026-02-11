pcap_remove_from_pcaps_to_close(pcap_t *p)
{
	pcap_t *pc, *prevpc;

	for (pc = pcaps_to_close, prevpc = NULL; pc != NULL;
	    prevpc = pc, pc = pc->md.next) {
		if (pc == p) {


			if (prevpc == NULL) {


				pcaps_to_close = pc->md.next;
			} else {


				prevpc->md.next = pc->md.next;
			}
			break;
		}
	}
}
