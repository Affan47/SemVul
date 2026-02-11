terminated(pid_t p, int s)
{
int	n;

	for (n=0; n<module_nchildren; n++)
		if (module_pids[n] == p)
		{
			module_pids[n]= -1;
			(*childfunc)(n, module_delids[n]);
			break;
		}
}
