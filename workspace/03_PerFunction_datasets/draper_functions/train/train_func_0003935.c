Amd7930_empty_Dfifo(struct IsdnCardState *cs, int flag)
{

	BYTE stat, der;
	BYTE *ptr;
	struct sk_buff *skb;


	if ((cs->debug & L1_DEB_ISAC) && !(cs->debug & L1_DEB_ISAC_FIFO))
		debugl1(cs, "Amd7930: empty_Dfifo");


	ptr = cs->rcvbuf + cs->rcvidx;


	AmdIrqOff(cs);


	stat = rByteAMD(cs, 0x07);


	while ((stat & 2) && ((ptr-cs->rcvbuf) < MAX_DFRAME_LEN_L1)) {
		*ptr = rByteAMD(cs, 0x04);
		ptr++;
		stat = rByteAMD(cs, 0x07);
		cs->rcvidx = ptr - cs->rcvbuf;


		if (stat & 1) {

			der = rWordAMD(cs, 0x03);


			if (!der && !flag) {
				rWordAMD(cs, 0x89);

				if ((cs->rcvidx) > 0) {
					if (!(skb = alloc_skb(cs->rcvidx, GFP_ATOMIC)))
						printk(KERN_WARNING "HiSax: Amd7930: empty_Dfifo, D receive out of memory!\n");
					else {

						if (cs->debug & L1_DEB_ISAC_FIFO) {
							char *t = cs->dlog;

							t += sprintf(t, "Amd7930: empty_Dfifo cnt: %d |", cs->rcvidx);
							QuickHex(t, cs->rcvbuf, cs->rcvidx);
							debugl1(cs, "%s", cs->dlog);
						}

						memcpy(skb_put(skb, cs->rcvidx), cs->rcvbuf, cs->rcvidx);
						skb_queue_tail(&cs->rq, skb);
					}
				}

			}

			ptr = cs->rcvbuf;
			cs->rcvidx = 0;
			schedule_event(cs, D_RCVBUFREADY);
		}
	}

	if (cs->rcvidx >= MAX_DFRAME_LEN_L1) {
		if (cs->debug & L1_DEB_WARN)
			debugl1(cs, "AMD7930: empty_Dfifo L2-Framelength overrun");
		cs->rcvidx = 0;
		return;
	}

	AmdIrqOn(cs);
}
