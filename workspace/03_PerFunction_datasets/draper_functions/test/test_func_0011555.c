find_pid(pid_t pid)
{
    unsigned long i;
    for (i = 0; i < max_children; i++)
	if (childtab[i] == pid)
	    return i;
    return (unsigned long)-1;
}
