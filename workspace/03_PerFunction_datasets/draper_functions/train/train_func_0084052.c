conf_set_start_operator(conf_t * conf)
{
	rb_dlink_node *ptr, *next;
	if(t_oper != NULL)
	{
		free_oper_conf(t_oper);
		t_oper = NULL;
	}
	RB_DLINK_FOREACH_SAFE(ptr, next, t_oper_list.head)
	{
		free_oper_conf(ptr->data);
		rb_dlinkDestroy(ptr, &t_oper_list);
	}

	t_oper = make_oper_conf();
	t_oper->name = rb_strdup(conf->subname);
	t_oper->flags = OPER_ENCRYPTED | OPER_OPERWALL | OPER_REMOTEBAN;
}
