forward_init(forward_t *forward, forward_t *from)
{
	if (from && from->init == FORWARD_INIT) {
		forward->cnt = from->cnt;
		forward->timeout = from->timeout;
		forward->nodelist = from->nodelist;
		forward->init = from->init;
	} else {
		forward->cnt = 0;
		forward->timeout = 0;
		forward->nodelist = NULL;
		forward->init = FORWARD_INIT;
	}
}
