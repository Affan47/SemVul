hud_reticle_clear_list(reticle_list *rlist)
{
	reticle_list *cur;
	for ( cur = GET_FIRST(rlist); cur != END_OF_LIST(rlist); cur = GET_NEXT(cur) ) {
		cur->flags = 0;
	}
	list_init(rlist);
}
