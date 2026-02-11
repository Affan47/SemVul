ssl_killall(void)
{
	rb_dlink_node *ptr, *next;
	ssl_ctl_t *ctl;
	RB_DLINK_FOREACH_SAFE(ptr, next, ssl_daemons.head)
	{
		ctl = ptr->data;
		if(ctl->dead)
			continue;
		ctl->dead = 1;
		ssld_count--;
		rb_kill(ctl->pid, SIGKILL);
	}
}
