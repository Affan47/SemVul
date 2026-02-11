copyact(inp,outp,actno) FILE *inp,*outp; int actno; {
    int c,bcnt;
    fprintf(outp,"case %d:\n",actno);
    while (c = getc(inp), (isspace(c) || c == C_L))
      if (c == '\n') lines++;
    if (c == '{') {
	bcnt = 1;
	fputs("    {",outp);
	while (bcnt > 0 && (c = getc(inp)) != EOF) {
	    if (c == '{') bcnt++;
	    else if (c == '}') bcnt--;
	    else if (c == '\n') lines++;
	    putc(c,outp);
	}
	if (bcnt > 0) fatal("action doesn't end");
    } else {
	while (c != '\n' && c != EOF) {
	    putc(c,outp);
	    c = getc(inp);
	}
	lines++;
    }
    fprintf(outp,"\n    break;\n");
}
