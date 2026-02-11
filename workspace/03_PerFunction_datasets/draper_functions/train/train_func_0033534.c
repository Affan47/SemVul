line(s, start, endd, size)
char *s;
int start, endd, *size;
{
    int col0,
	ip;
    unsigned char c;

    col0 = ixp = curpos.x;
    ip = start;
    tabptr = 0;
    while (1) {
	c = readchar();
	if (movemap[c] == INSMACRO)
	    insertmacro(mbuffer[lookup(c)].m_text, 1);
	else if (c == DW) {
	    while (!wc(s[ip-1]) && ip > start)
		back_up(s[--ip]);
	    while (wc(s[ip-1]) && ip > start)
		back_up(s[--ip]);
	}
	else if (c == eraseline) {
	    ip = start;
	    tabptr = 0;
	    mvcur(-1,ixp=col0);
	}
	else if (c==Erasechar) {
	    if (ip>start)
		back_up(s[--ip]);
	    else {
		*size = 0;
		return(0);
	    }
	}
	else if (c=='\r' || c==ESC) {
	    *size = (ip-start);
            return (c==ESC) ? ESC : EOL;
	}
	else if ((!beautify) || c == TAB || c == ''
			     || (c >= ' ' && c <= '~')) {
	    if (ip < endd) {
		if (c == '')
		    c = readchar();
		switch (cclass(c)) {
		    case 0 : ixp++; break;
		    case 1 : ixp += 2; break;
		    case 2 :
			tabstack[tabptr++] = ixp;
			ixp = tabsize*(1+(ixp/tabsize));
			break;
		    case 3 : ixp += 3; break;
		}
		s[ip++] = c;
		printch(c);
	    }
	    else
		error();
	}
        else
	    error();
    }
}
