Clear(const char *file, unsigned int line)
{
	if (lengthAllocated)
		rakFree_Ex(data, file, line );
	readOffset=writeOffset=lengthAllocated=0;
	data=0;
}
