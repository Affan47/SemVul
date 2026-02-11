timer_ticker(struct sr_timer *timer_list)
{
	struct sr_timer* t;

	for (t=timer_list;t; t=t->next){
		if (*jiffies>=t->expires){
			t->expires=*jiffies+t->interval;
			t->u.timer_f(*jiffies, t->t_param);
		}
	}
}
