EWMH_DeleteWmIcon(FvwmWindow *fw, Bool mini_icon, Bool icon)
{
	CARD32 *list;
	CARD32 *new_list = NULL;
	int keep_start = 0, keep_length = 0;
	int s;
	int i;

	if (mini_icon && icon)
	{
		ewmh_DeleteProperty(
			FW_W(fw), "_NET_WM_ICON",
			EWMH_ATOM_LIST_PROPERTY_NOTIFY);
		fw->ewmh_mini_icon_width = 0;
		fw->ewmh_mini_icon_height = 0;
		fw->ewmh_icon_width = 0;
		fw->ewmh_icon_height = 0;

		return;
	}

	list = ewmh_AtomGetByName(
		FW_W(fw),"_NET_WM_ICON", EWMH_ATOM_LIST_PROPERTY_NOTIFY, &s);
	if (list == NULL)
	{
		return;
	}
	s = s / sizeof(CARD32);

	if (FMiniIconsSupported && list != NULL)
	{
		int k_width = (mini_icon) ? fw->ewmh_icon_width :
			fw->ewmh_mini_icon_width;
		int k_height = (mini_icon) ? fw->ewmh_icon_height :
			fw->ewmh_mini_icon_height;

		for (i = 0; i < s - 1; )
		{
			if (i + 1 + list[i]*list[i+1] < s)
			{
				if (list[i] == k_width &&
				    list[i+1] == k_height)
				{
					keep_start = i;
					keep_length =  2 + list[i]*list[i+1];
					i = s;
				}
			}
			if (i != s && list[i]*list[i+1] > 0)
			{
				i = i + 2 + list[i]*list[i+1];
			}
			else
			{
				i = s;
			}
		}
	}

	if (keep_length > 0)
	{
		new_list = (CARD32 *)safemalloc(keep_length * sizeof(CARD32));
		memcpy(
			new_list, &list[keep_start],
			keep_length * sizeof(CARD32));
	}

	if (new_list != NULL)
	{
		ewmh_ChangeProperty(
			FW_W(fw),"_NET_WM_ICON",
			EWMH_ATOM_LIST_PROPERTY_NOTIFY,
			(unsigned char *)new_list, keep_length);
	}
	else
	{

		ewmh_DeleteProperty(
			FW_W(fw), "_NET_WM_ICON",
			EWMH_ATOM_LIST_PROPERTY_NOTIFY);
	}

	if (mini_icon)
	{
		fw->ewmh_mini_icon_width = 0;
		fw->ewmh_mini_icon_height = 0;
	}
	if (icon)
	{
		fw->ewmh_icon_width = 0;
		fw->ewmh_icon_height = 0;
	}
	if (new_list != NULL)
	{
		free(new_list);
	}
	free(list);
}
