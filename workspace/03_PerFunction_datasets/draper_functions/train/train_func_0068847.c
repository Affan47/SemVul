post(void (*func)(), int nparam, intptr_t param, intptr_t param2)
{
	EVENT_POST *ep;


	ALLOC(&ep, sizeof(EVENT_POST), "EVENT_post");

	ep->func = func;
	ep->nparam = nparam;
	ep->param = param;
	ep->param2 = param2;

	LIST_insert(&_post_list, ep, &ep->list);

	HOOK(post)();
}
