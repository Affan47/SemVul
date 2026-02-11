as_user_delete(struct s_as_player *p)
{
	char *text = as_argv[as_current+1];

	if (text == NULL)
		text = "karma police";

	as_send(p, Msg, text);
	as_send(p, Kick, "");
	as_del_player(p);
}
