str_out(char *p, int action)
{
	static char *strop_tb[] = {
		"show",
		"showc",
		"showr",
		"lyshow",
		"gcshow",
		"anshow",
		"gxshow",
	};
	if (curft <= 0)
		curft = defft;


	if (*p == '$' && isdigit((unsigned char) p[1])
	 && (unsigned) (p[1] - '0') < FONT_UMAX) {
		if (curft != p[1] - '0') {
			curft = p[1] - '0';
			if (curft == 0)
				curft = defft;
		}
		p += 2;
	}

#ifdef HAVE_PANGO


	if (cfmt.pango) {
		if (cfmt.pango == 2 || !is_latin((unsigned char *) p)) {
			str_pg_out(p, action);
			return;
		}
	}
#endif


	if (strchr(p, '$') == 0) {
		strop = strop_tb[action];
		str_ft_out(p, 1);
		return;
	}


	switch (action) {
	case A_CENTER:
	case A_RIGHT:
		if (!svg && epsf != 2) {
			PUT0("/str{");
			outft = -1;
			strop = "strop";
			break;
		}

	default:
		strop = strop_tb[action];
		break;
	}

	str_ft_out(p, 1);


	if (svg || epsf == 2)
		return;
	if (action == A_CENTER || action == A_RIGHT) {
		PUT0("}def\n"
			"/strop/strw load def/w 0 def str w ");
		if (action == A_CENTER)
			PUT0("0.5 mul ");
		PUT0("neg 0 RM/strop/show load def str ");
	}
}
