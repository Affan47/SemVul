rfbUnregisterProtocolExtension(rfbProtocolExtension* extension)
{

	rfbProtocolExtension *cur = NULL, *pre = NULL;

	if(extension == NULL)
		return;

	if (! extMutex_initialized) {
		INIT_MUTEX(extMutex);
		extMutex_initialized = 1;
	}

	LOCK(extMutex);

	if(rfbExtensionHead == extension) {
		rfbExtensionHead = rfbExtensionHead->next;
		UNLOCK(extMutex);
		rfbUnregisterProtocolExtension(extension->next);
		return;
	}

	cur = pre = rfbExtensionHead;

	while(cur) {
		if(cur == extension) {
			pre->next = cur->next;
			break;
		}
		pre = cur;
		cur = cur->next;
	}

	UNLOCK(extMutex);

	rfbUnregisterProtocolExtension(extension->next);
}
