restoreall(void)
{
	while(fp>=frame && fp->sp){
		restore(fp->sp);
		--fp;
	}
	fp = frame;
}
