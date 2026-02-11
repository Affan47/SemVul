parse(int c) {
	printf("\x1b[01;31m%c:%c[%.*s]\x1b[00m",state,c,(int)(stack-b_stack),b_stack);
	switch(state) {
	case 'C':
		if(c=='I') { out1("arg"); }
		if(c=='{') { *stack++='('; state='X';  }
		break;
	case 'F':
		state='X';
		if(c=='=' && stack>b_stack && stack[-1]=='v') { out1("local"); }
		out1(c=='=' ? "ident" : "get");
	case 'P':
		if(c=='(') { *stack++='f'; *stack++='('; outo('('); break; }
	case 'X':
		if(c=='N') { out1("num"); }
		else if(c=='I') {
			int l=ident-b_ident;
			if(l==8&&memcmp("function",b_ident,ident-b_ident)==0) { state='C'; outn("def",closuren); outn("args",closuren); *fstack++=closuren++; }
			else if(l==3&&memcmp("var",b_ident,ident-b_ident)==0) { *stack++='v'; }
			else if(l==6&&memcmp("return",b_ident,ident-b_ident)==0) { *stack++='r'; }
			else { state='F'; } }
		else if(c==';') { unstack(0); outo(';'); }
		else if(c=='(') { *stack++='('; out1("com ("); }
		else if(c==')') { unstack(0); stack--; state='P'; }
		else if(c=='}') { unstack(0); stack--; outn("end",*(--fstack)); }
		else { unstack(c); *stack++=c; }
		break;
	default:
		goto abort;
	}
	return;

abort:	printf("\n Parse abort: char '%c' state '%c'\n",c,state);
	abort();
}
