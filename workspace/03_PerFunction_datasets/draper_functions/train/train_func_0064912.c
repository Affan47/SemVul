execcmds(io *f)
{
	static int first = 1;
	if(first){
		rdcmds[0].i = 1;
		rdcmds[1].f = Xrdcmds;
		rdcmds[2].f = Xreturn;
		first = 0;
	}
	start(rdcmds, 1, runq->local);
	runq->cmdfd = f;
	runq->iflast = 0;
}
