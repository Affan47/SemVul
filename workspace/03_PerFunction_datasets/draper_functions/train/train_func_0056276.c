condition_macro(int cc, int target)
{
	cur = &pifstack[piflevel];
	if (cc == SHARP_IFDEF || cc == SHARP_IFNDEF || cc == SHARP_IF) {
		DBG_PRINT(piflevel, "#if");
		if (++piflevel >= MAXPIFSTACK)
			die("#if pifstack over flow. [%s]", curfile);
		++cur;
		cur->start = level;
		cur->end = -1;
		cur->if0only = 0;
		if (peekc(0) == '0')
			cur->if0only = 1;
		else if ((cc = nexttoken(NULL, cpp_reserved_word)) == SYMBOL && !strcmp(token, "notdef"))
			cur->if0only = 1;
		else
			pushbacktoken();
	} else if (cc == SHARP_ELIF || cc == SHARP_ELSE) {
		DBG_PRINT(piflevel - 1, "#else");
		if (cur->end == -1)
			cur->end = level;
		else if (cur->end != level && wflag)
			warning("uneven level. [+%d %s]", lineno, curfile);
		level = cur->start;
		cur->if0only = 0;
	} else if (cc == SHARP_ENDIF) {
		int minus = 0;

		--piflevel;
		if (piflevel < 0) {
			minus = 1;
			piflevel = 0;
		}
		DBG_PRINT(piflevel, "#endif");
		if (minus) {
			if (wflag)
				warning("#if block unmatched. reseted. [+%d %s]", lineno, curfile);
		} else {
			if (cur->if0only)
				level = cur->start;
			else if (cur->end != -1) {
				if (cur->end != level && wflag)
					warning("uneven level. [+%d %s]", lineno, curfile);
				level = cur->end;
			}
		}
	}
	while ((cc = nexttoken(NULL, cpp_reserved_word)) != EOF && cc != '\n') {
                if (cc == SYMBOL && strcmp(token, "defined") != 0) {
			if (target == REF) {
				if (defined(token))
		                        PUT(token, lineno, sp);
			} else if (target == SYM) {
				if (!defined(token))
		                	PUT(token, lineno, sp);
			}
		}
	}
}
