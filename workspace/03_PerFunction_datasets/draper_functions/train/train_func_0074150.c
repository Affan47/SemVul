mg_color_insert (GtkWidget *item, gpointer userdata)
{
	char buf[32];
	char *text;
	int num = GPOINTER_TO_INT (userdata);

	if (num > 99)
	{
		switch (num)
		{
		case 100:
			text = "\002"; break;
		case 101:
			text = "\037"; break;
		case 102:
			text = "\035"; break;
		default:
			text = "\017"; break;
		}
		key_action_insert (current_sess->gui->input_box, 0, text, 0, 0);
	} else
	{
		sprintf (buf, "\003%02d", num);
		key_action_insert (current_sess->gui->input_box, 0, buf, 0, 0);
	}
}
