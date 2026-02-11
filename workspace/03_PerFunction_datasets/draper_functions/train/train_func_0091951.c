IoEvent_handleEvent(int fd, short eventType, void *context)
{
	IoEvent *self = (IoEvent *)context;
	struct event *ev = IoEvent_rawEvent(self);
	IoEventManager *em = IoState_protoWithInitFunction_(IOSTATE, protoId);


	if(!IoEventManager_rawHasActiveEvent_(em, self))
	{
		printf("ERROR: got IoEvent_handleEvent for Event not in EventManager active list\n");
		exit(-1);
	}

	if (!ev)
	{
		printf("IoEventManager_addEvent: attempt to process an IoEvent with a 0x0 event struct - possible gc error");
		exit(1);
	}


	IoState_pushRetainPool(IOSTATE);

	if(eventType == EV_TIMEOUT)
	{
		IoMessage *m = DATA(em)->handleEventMessageTrue;
		IoMessage_locals_performOn_(m, self, self);
	}
	else
	{
		IoMessage *m = DATA(em)->handleEventMessageFalse;
		IoMessage_locals_performOn_(m, self, self);
	}
	IoState_popRetainPool(IOSTATE);
	IoEventManager_rawRemoveEvent_(em, self);

}
