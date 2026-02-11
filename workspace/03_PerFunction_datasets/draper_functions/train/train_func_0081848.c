_out(int typ)
{
    int i, t;
    for(i=0;i<define_no;i++) {
	t=define[i].type;
	if(directives[t].type!=typ) continue;
	if(typ==t_def && define[i].tag!=deftag) continue;
	directives[t].processor(define[i].parm);
    }
}
