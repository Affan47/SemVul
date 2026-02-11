process_msg_replydata(postreply_t *postreply)
{
	GtkWidget *widget;
	char **arr0 = NULL, **arr = NULL;
	msg_t *msg = NULL;
	int i = 1;
	static gboolean first_call = TRUE;


	widget = lookup_widget(window1, "label132");


	if(postreply->status_code == 200 && postreply->size > 0)
	{
		arr0 = g_strsplit (postreply->data, "###", -1);


		if (arr0[0] && strlen(arr0[0]))
		{
			char *err_msg;

			arr = g_strsplit (arr0[0], "|", -1);

			err_msg	= g_strdup(arr[4]);
			gtk_label_set_label(GTK_LABEL(widget), err_msg );


			if(atoi(arr[6]) > 0)
			{

				db_ts_last_request_friends = g_strdup(arr[2]);

				if(first_call)
				{
					GtkWidget *widget = NULL;

					widget = lookup_widget(window1, "button35");
					gtk_widget_show(widget);

					first_call = FALSE;
				}
				else
					global_new_msg = TRUE;
			}


			g_strfreev(arr);
		}


		while (arr0[i] && strlen(arr0[i]) )
		{


			msg = g_new0(msg_t, 1);


			arr = g_strsplit (arr0[i], "|||", -1);


			msg->id 	= atoi(arr[1]);
			msg->time	= g_strdup(arr[2]);
			msg->txt	= g_strdup(arr[3]);
			msg->from	= g_strdup(arr[4]);
			msg->to		= g_strdup(arr[5]);
			msg->lat	= atof(arr[6]);
			msg->lon	= atof(arr[7]);
			msg->incoming	= TRUE;


			add_message(msg);

			i++;

			g_strfreev(arr);
		}
	}
	else
	{
		gtk_label_set_label (GTK_LABEL(widget),
		                     g_strdup_printf (_("msg-code: %d"),
		                                      (int)postreply->status_code));
	}


}
