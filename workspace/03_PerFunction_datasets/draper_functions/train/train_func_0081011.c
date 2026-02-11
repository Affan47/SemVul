delete_loop(struct loop *loop)
{
	struct frame *frame = loop->var.frame;
	struct deletion *del;
	struct loop *walk, *prev;

	groups++;
	prev = NULL;
	for (walk = frame->loops; walk != loop; walk = walk->next)
		prev = walk;
	if (prev)
		prev->next = loop->next;
	else
		frame->loops = loop->next;
	del = new_deletion(dt_loop);
	del->u.loop.ref = loop;
	del->u.loop.prev = prev;
}
