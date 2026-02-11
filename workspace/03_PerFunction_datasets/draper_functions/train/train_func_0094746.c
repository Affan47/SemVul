looper(File *f, Cmd *cp, int xy)
{
	Posn p, op;
	Range r;

	r = addr.r;
	op= xy? -1 : r.p1;
	nest++;
	compile(cp->re);
	for(p = r.p1; p<=r.p2; ){
		if(!execute(f, p, r.p2)){
			if(xy || op>r.p2)
				break;
			f->dot.r.p1 = op, f->dot.r.p2 = r.p2;
			p = r.p2+1;
		}else{
			if(sel.p[0].p1==sel.p[0].p2){
				if(sel.p[0].p1==op){
					p++;
					continue;
				}
				p = sel.p[0].p2+1;
			}else
				p = sel.p[0].p2;
			if(xy)
				f->dot.r = sel.p[0];
			else
				f->dot.r.p1 = op, f->dot.r.p2 = sel.p[0].p1;
		}
		op = sel.p[0].p2;
		cmdexec(f, cp->ccmd);
		compile(cp->re);
	}
	--nest;
}
