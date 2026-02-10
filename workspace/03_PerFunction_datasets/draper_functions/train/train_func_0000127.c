addpatchvalues(struct patchinfo *p)
{
	int p2p = p->p2p;
	addpatchstring("WATCHDOG", "1");
	addpatchbyte("AutoFrame", 1);
   	switch (p->protocol) {
      		case DP_CT1:
         		addpatchbyte("PROTOCOL", 1);
	 		break;
      		case DP_VN3:
         		addpatchbyte("PROTOCOL", 2);
	 		break;
      		case DP_NI1:
	 		p2p = 0;
         		addpatchbyte("PROTOCOL", 3);
	 		if (p->dn1 && p->spid1) {
            			addpatchstring("DN", p->dn1);
            			addpatchstring("SPID", p->spid1);
	 		}
	 		if (p->dn2 && p->spid2) {
            			addpatchstring("DN2", p->dn2);
            			addpatchstring("SPID2", p->spid2);
	 		}
	 		break;
      		case DP_AUSTEL:
         		addpatchbyte("PROTOCOL", 4);
	 		break;
      		case DP_5ESS:
	 		p2p = 0;
         		addpatchbyte("PROTOCOL", 5);
	 		if (p->dn1 && p->spid1) {
            			addpatchstring("DN", p->dn1);
            			addpatchstring("SPID", p->spid1);
	 		}
	 		if (p->dn2 && p->spid2) {
            			addpatchstring("DN2", p->dn2);
            			addpatchstring("SPID2", p->spid2);
	 		}
	 		break;
   	}
   	if (p2p) {
		addpatchbyte("P2P", 1);
		addpatchbyte("TEI", 0);
   	}
}
