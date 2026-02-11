event_to_wire(Display *dpy, XEvent *event, xEvent *wire)
{
    XExtDisplayInfo *info = find_display(dpy);
    XSyncCounterNotifyEvent *aevent;
    xSyncCounterNotifyEvent *awire;
    XSyncAlarmNotifyEvent *anl;
    xSyncAlarmNotifyEvent *ane;

    SyncCheckExtension(dpy, info, False);

    switch ((event->type & 0x7F) - info->codes->first_event)
    {
      case XSyncCounterNotify:
	awire = (xSyncCounterNotifyEvent *) wire;
	aevent = (XSyncCounterNotifyEvent *) event;
	awire->type = aevent->type | (aevent->send_event ? 0x80 : 0);
	awire->sequenceNumber = aevent->serial & 0xFFFF;
	awire->counter = aevent->counter;
	awire->wait_value_lo = XSyncValueLow32(aevent->wait_value);
	awire->wait_value_hi = XSyncValueHigh32(aevent->wait_value);
	awire->counter_value_lo = XSyncValueLow32(aevent->counter_value);
	awire->counter_value_hi = XSyncValueHigh32(aevent->counter_value);
	awire->time = aevent->time;
	awire->count = aevent->count;
	awire->destroyed = aevent->destroyed;
	return True;

      case XSyncAlarmNotify:
	ane = (xSyncAlarmNotifyEvent *) wire;
	anl = (XSyncAlarmNotifyEvent *) event;
	ane->type = anl->type | (anl->send_event ? 0x80 : 0);
	ane->sequenceNumber = anl->serial & 0xFFFF;
	ane->alarm = anl->alarm;
	ane->counter_value_lo = XSyncValueLow32(anl->counter_value);
	ane->counter_value_hi = XSyncValueHigh32(anl->counter_value);
	ane->alarm_value_lo = XSyncValueLow32(anl->alarm_value);
	ane->alarm_value_hi = XSyncValueHigh32(anl->alarm_value);
	ane->state = anl->state;
	ane->time = anl->time;
	return True;
    }
    return False;
}
