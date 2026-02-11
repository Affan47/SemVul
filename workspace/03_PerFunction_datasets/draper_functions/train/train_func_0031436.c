rfbUnregisterSecurityHandler(rfbSecurityHandler* handler)
{
	rfbSecurityHandler *cur = NULL, *pre = NULL;

	if(handler == NULL)
		return;

	if(securityHandlers == handler) {
		securityHandlers = securityHandlers->next;
		rfbUnregisterSecurityHandler(handler->next);
		return;
	}

	cur = pre = securityHandlers;

	while(cur) {
		if(cur == handler) {
			pre->next = cur->next;
			break;
		}
		pre = cur;
		cur = cur->next;
	}
	rfbUnregisterSecurityHandler(handler->next);
}
