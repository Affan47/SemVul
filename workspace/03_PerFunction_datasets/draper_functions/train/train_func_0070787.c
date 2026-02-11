GetWindowConfig (TwmWindow *theWindow, short *x, short *y,
		     unsigned short *width, unsigned short *height,
		     Bool *iconified, Bool *icon_info_present,
		     short *icon_x, short *icon_y,
		     Bool *width_ever_changed_by_user,
		     Bool *height_ever_changed_by_user,
		     int *occupation)


{
    char *clientId, *windowRole;
    TWMWinConfigEntry *ptr;
    int found = 0;

    ptr = winConfigHead;

    if (!ptr)
	return 0;

    clientId = GetClientID (theWindow->w);
    windowRole = GetWindowRole (theWindow->w);

    while (ptr && !found)
    {
	int client_id_match = (!clientId && !ptr->client_id) ||
	    (clientId && ptr->client_id &&
	    strcmp (clientId, ptr->client_id) == 0);

	if (!ptr->tag && client_id_match)
	{
	    if (windowRole || ptr->window_role)
	    {
		found = (windowRole && ptr->window_role &&
		    strcmp (windowRole, ptr->window_role) == 0);
	    }
	    else
	    {


		if (strcmp (theWindow->class.res_name,
			ptr->class.res_name) == 0 &&
		    strcmp (theWindow->class.res_class,
			ptr->class.res_class) == 0 &&
		   (ptr->wm_name == NULL ||
		    strcmp (theWindow->name, ptr->wm_name) == 0))
		{
		    if (clientId)
		    {


			found = 1;
		    }
		    else
		    {


			char **wm_command = NULL;
			int wm_command_count = 0, i;

			XGetCommand (dpy, theWindow->w,
			    &wm_command, &wm_command_count);

			if (wm_command_count == ptr->wm_command_count)
			{
			    for (i = 0; i < wm_command_count; i++)
				if (strcmp (wm_command[i],
				    ptr->wm_command[i]) != 0)
				    break;

			    if (i == wm_command_count)
				found = 1;
			}
		    }
		}
	    }
	}

	if (!found)
	    ptr = ptr->next;
    }

    if (found)
    {
	*x = ptr->x;
	*y = ptr->y;
	*width = ptr->width;
	*height = ptr->height;
	*iconified = ptr->iconified;
	*icon_info_present = ptr->icon_info_present;
	*width_ever_changed_by_user = ptr->width_ever_changed_by_user;
	*height_ever_changed_by_user = ptr->height_ever_changed_by_user;

	if (*icon_info_present)
	{
	    *icon_x = ptr->icon_x;
	    *icon_y = ptr->icon_y;
	}

	*occupation = ptr->occupation;

	ptr->tag = 1;
    }
    else
	*iconified = 0;

    if (clientId)
	XFree (clientId);

    if (windowRole)
	XFree (windowRole);

    return found;
}
