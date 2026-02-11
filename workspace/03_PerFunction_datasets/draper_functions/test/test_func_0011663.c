findlabel(char *name)
{
	register struct label *q;

	q=searchlabel(name);
	if ( q==NULL )
		q=makelabel(name, UNDEF|FORWARD|NOREDEF,
				asmflags&F_RELATIF ? L_RELATIVE : L_ABSOLUTE );
	q->flags |= USED;
	return q;
}
