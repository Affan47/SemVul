timer_sanity_check()
{
    timer_element *curr;
    char obj_address[20];


    for (curr = timer_base; curr; curr = curr->next)
	if (curr->kind == TIMER_OBJECT) {
	    struct obj *obj = (struct obj *) curr->arg;
	    if (obj->timed == 0) {
		pline("timer sanity: untimed obj %s, timer %ld",
		      fmt_ptr((genericptr_t)obj, obj_address), curr->tid);
	    }
	}
}
