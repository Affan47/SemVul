ctrl_channelfreq_set(struct pvr2_ctrl *cptr,int m,int v)
{
	struct pvr2_hdw *hdw = cptr->hdw;
	unsigned int slotId = hdw->freqProgSlot;
	if ((slotId > 0) && (slotId <= FREQTABLE_SIZE)) {
		hdw->freqTable[slotId-1] = v;


		if (hdw->freqSelector) {
			if (hdw->freqSlotRadio == slotId) {
				hdw->freqSlotRadio = 0;
			}
		} else {
			if (hdw->freqSlotTelevision == slotId) {
				hdw->freqSlotTelevision = 0;
			}
		}
	}
	return 0;
}
