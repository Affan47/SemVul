insert_timer(gnu)
    timer_element *gnu;
{
    timer_element *curr, *prev;

    for (prev = 0, curr = timer_base; curr; prev = curr, curr = curr->next)
	if (curr->timeout >= gnu->timeout) break;

    gnu->next = curr;
    if (prev)
	prev->next = gnu;
    else
	timer_base = gnu;
}
