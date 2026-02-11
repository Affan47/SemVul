process_message(unsigned long type, unsigned long *body)
{
	struct ConfigWinPacket  *cfgpacket;

	switch (type)
	{
	case M_NEW_DESK:
		new_desk = body[0];
		{
			int button = -1;
			button_info *b, *ub;

			ub = UberButton;
			while (NextButton(&ub, &b, &button, 1))
			{
				RedrawButton(b, DRAW_FORCE, NULL);
			}
		    }
		break;
	case M_END_WINDOWLIST:
		SpawnSome();
		break;
	case M_MAP:
		swallow(body);
		break;
	case M_RES_NAME:
	case M_RES_CLASS:
	case M_WINDOW_NAME:
		CheckForHangon(body);
		break;
	case M_CONFIG_INFO:
		handle_config_info_packet((unsigned long*)body);
		break;
	case M_ADD_WINDOW:
	case M_CONFIGURE_WINDOW:
		cfgpacket = (void *) body;
		if (cfgpacket->w == MyWindow)
		{
			button_lborder = button_rborder = button_tborder
				= button_bborder = cfgpacket->border_width;
			switch (GET_TITLE_DIR(cfgpacket))
			{
			case DIR_N:
				button_tborder += cfgpacket->title_height;
				break;
			case DIR_S:
				button_bborder += cfgpacket->title_height;
				break;
			case DIR_W:
				button_lborder += cfgpacket->title_height;
				break;
			case DIR_E:
				button_rborder += cfgpacket->title_height;
				break;
			}
		}
		break;
	case MX_PROPERTY_CHANGE:
		if (body[0] == MX_PROPERTY_CHANGE_BACKGROUND &&
			((!swallowed && body[2] == 0)
			|| (swallowed && body[2] == MyWindow)))
		{
			if (CSET_IS_TRANSPARENT_PR(UberButton->c->colorset))
			{
				update_root_transparency(NULL);
			}
		}
		else if (body[0] == MX_PROPERTY_CHANGE_SWALLOW
			&& body[2] == MyWindow)
		{
			char *str;
			unsigned long u;
			Window s, swin;
			char cmd[256];
			button_info *b, *ub = UberButton;
			int button = -1;

			str = (char *)&body[3];
			swallowed = body[1];
			if (swallowed && str && sscanf(str, "%lu", &u) == 1)
			{
				swallower_win = (Window)u;
			}
			else
			{
				swallower_win = 0;
			}

			s = ((swallower_win && swallowed) ? swallower_win :
				MyWindow);
			while (NextButton(&ub, &b, &button, 0))
			{
				swin = SwallowedWindow(b);
				if ((buttonSwallowCount(b) == 3) && swin)
				{
					sprintf(cmd,
						"PropertyChange %u %u %lu %lu",
						MX_PROPERTY_CHANGE_SWALLOW, 1,
						swin, s);
					SendText(fd, cmd, 0);
				}
			}
		}
		break;
	case M_STRING:
		parse_message_line((char *)&body[3]);
		break;
	default:
		break;
	}
}
