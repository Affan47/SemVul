checkfunc()
{	int i;

	if (functop<=0) {
		yyerror("no executable code");
		return;
	}
	for (i=0; i<functop; i++)
		if (function[i].pos<0)
			linkstdfunc(i);

	for (i=0; i<pc; i++)
		switch (code[i].op) {
		case CALL:
			if (code[i].f1>=0)
				code[i].f1=function[code[i].f1].pos;
			break;
		case FUNCENT:
		case FUNCRET:
			code[i].f1=function[code[i].f1].localsize;
			break;
		default:
			break;
		}
}
