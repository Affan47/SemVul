mmstyle (header *hd)
{	header *st=hd,*res;
	hd=getvalue(hd); if (error) return;
	if (hd->type!=s_string)
	{	output("Argument for markerstyle must be a string!\n");
		error=90; return;
	}
	switch (markertype)
	{	case marker_cross : res=new_string("x",8,""); break;
		case marker_circle : res=new_string("o",8,""); break;
		case marker_diamond : res=new_string("<>",8,""); break;
		case marker_dot : res=new_string(".",8,""); break;
		case marker_plus : res=new_string("+",8,""); break;
		case marker_square : res=new_string("[]",8,""); break;
		case marker_star : res=new_string("*",8,""); break;
		default : res=new_string("",8,"");
	}
	if (!strcmp(stringof(hd),"x")) markertype=marker_cross;
	else if (!strcmp(stringof(hd),"o")) markertype=marker_circle;
	else if (!strcmp(stringof(hd),"<>")) markertype=marker_diamond;
	else if (!strcmp(stringof(hd),".")) markertype=marker_dot;
	else if (!strcmp(stringof(hd),"+")) markertype=marker_plus;
	else if (!strcmp(stringof(hd),"[]")) markertype=marker_square;
	else if (!strcmp(stringof(hd),"*")) markertype=marker_star;
	moveresult(st,res);
}
