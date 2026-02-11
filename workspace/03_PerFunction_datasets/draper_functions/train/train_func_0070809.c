closePipe(void)
{
	DPRINTF("closing pipe");
	if (lastIn >= 0)	{ close(lastIn); lastIn = -1; }
	if (lastOut >= 0)	{ close (lastOut); lastOut = -1; }
	if (childPID > 1)	{ eliminatePipe(childPID); childPID = -1; }
}
