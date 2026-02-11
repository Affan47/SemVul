menu_toggle_cb (GtkCheckMenuItem *item, menu_entry *me)
{
	me->state = 0;
	if (item->active)
		me->state = 1;


	menu_foreach_gui (me, menu_update_cb);

	if (me->state)
		handle_command (current_sess, me->cmd, FALSE);
	else
		handle_command (current_sess, me->ucmd, FALSE);
}
