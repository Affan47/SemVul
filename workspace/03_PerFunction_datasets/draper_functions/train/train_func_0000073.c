ParseSwallow(
	char **ss, unsigned int *flags, unsigned int *mask, button_info *b)
{
	char *swallowopts[] =
	{
		"nohints", "hints",
		"nokill", "kill",
		"noclose", "close",
		"respawn", "norespawn",
		"useold", "noold",
		"usetitle", "notitle",
		"fvwmmodule", "nofvwmmodule",
		"swallownew",
		NULL
	};
	char *t, *s = *ss;

	while (*s && *s != ')')
	{
		s = trimleft(s);
		if (*s == ',')
		{
			s++;
			continue;
		}

		switch (GetTokenIndex(s, swallowopts, -1, &s))
		{
		case 0:
			*flags |= b_NoHints;
			*mask |= b_NoHints;
			break;
		case 1:
			*flags &= ~b_NoHints;
			*mask |= b_NoHints;
			break;
		case 2:
			*flags &= ~b_Kill;
			*mask |= b_Kill;
			break;
		case 3:
			*flags |= b_Kill;
			*mask |= b_Kill;
			break;
		case 4:
			*flags |= b_NoClose;
			*mask |= b_NoClose;
			break;
		case 5:
			*flags &= ~b_NoClose;
			*mask |= b_NoClose;
			break;
		case 6:
			*flags |= b_Respawn;
			*mask |= b_Respawn;
			b->newflags.do_swallow_new = 0;
			break;
		case 7:
			*flags &= ~b_Respawn;
			*mask |= b_Respawn;
			b->newflags.do_swallow_new = 0;
			break;
		case 8:
			*flags |= b_UseOld;
			*mask |= b_UseOld;
			break;
		case 9:
			*flags &= ~b_UseOld;
			*mask |= b_UseOld;
			break;
		case 10:
			*flags |= b_UseTitle;
			*mask |= b_UseTitle;
			break;
		case 11:
			*flags &= ~b_UseTitle;
			*mask |= b_UseTitle;
			break;
		case 12:
			*flags |= b_FvwmModule;
			*mask |= b_FvwmModule;
			break;
		case 13:
			*flags &= ~b_FvwmModule;
			*mask |= b_FvwmModule;
			break;
		case 14:
			*flags &= ~b_Respawn;
			*mask |= b_Respawn;
			b->newflags.do_swallow_new = 1;
			break;
		default:
			t = seekright(&s);
			fprintf(stderr,
				"%s: Illegal Swallow option \"%s\"\n", MyName,
				(t) ? t : "");
			if (t)
			{
				free(t);
			}
		}
	}
	if (*s)
	{
		s++;
	}
	*ss = s;
}
