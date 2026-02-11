ewmh_WMState(EWMH_CMD_ARGS)
{
	unsigned long maximize = 0;

	if (ev != NULL)
	{
		ewmh_atom *a1,*a2;

		a1 = ewmh_GetEwmhAtomByAtom(
			ev->xclient.data.l[1], EWMH_ATOM_LIST_WM_STATE);
		a2 = ewmh_GetEwmhAtomByAtom(
			ev->xclient.data.l[2], EWMH_ATOM_LIST_WM_STATE);

		if (a1 != NULL)
		{
			maximize |= a1->action(fw, ev, NULL, 0);
		}
		if (a2 != NULL)
		{
			maximize |= a2->action(fw, ev, NULL, 0);
		}
	}
	else if (style != NULL)
	{
		CARD32 *val;
		unsigned int nitems;
		int size = 0;
		int i;
		ewmh_atom *list = ewmh_atom_wm_state;
		int has_hint = 0;

		val = ewmh_AtomGetByName(
			FW_W(fw), "_NET_WM_STATE", EWMH_ATOM_LIST_CLIENT_WIN,
			&size);

		if (val == NULL)
		{
			size = 0;
		}

#if DEBUG_EWMH_INIT_STATE
		if (size != 0)
		{
			fprintf(
				stderr, "Window 0x%lx has an init"
				" _NET_WM_STATE hint\n",FW_W(fw));
		}
#endif
		nitems = size / sizeof(CARD32);
		while(list->name != NULL)
		{
			has_hint = 0;
			for(i = 0; i < nitems; i++)
			{
				if (list->atom == val[i])
				{
					has_hint = 1;
				}
			}
			list->action(fw, NULL, style, has_hint);
			list++;
		}
		if (val != NULL)
		{
			free(val);
		}
		return 0;
	}

	if (maximize != 0)
	{
		int max_vert = (maximize & EWMH_MAXIMIZE_VERT)? 100:0;
		int max_horiz = (maximize & EWMH_MAXIMIZE_HORIZ)? 100:0;
		char cmd[256];

		if (maximize & EWMH_MAXIMIZE_REMOVE)
		{
			sprintf(cmd,"Maximize off");
		}
		else
		{
			if (!is_function_allowed(
				    F_MAXIMIZE, NULL, fw, RQORIG_PROGRAM_US,
				    False))
			{
				return 0;
			}
			sprintf(cmd,"Maximize on %i %i", max_horiz, max_vert);
		}
		execute_function_override_window(NULL, NULL, cmd, 0, fw);
	}
	return 0;
}
