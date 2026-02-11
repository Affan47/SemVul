addChildProcess(DUL_ASSOCIATESERVICEPARAMETERS * service,
		int pid, LST_HEAD ** list)
{
    PROCESS_ELEMENT
    * e;

    if ((e = malloc(sizeof(*e))) == NULL)
	return 0;
    strcpy(e->callingAPTitle, service->callingAPTitle);
    strcpy(e->calledAPTitle, service->calledAPTitle);
    e->pid = pid;

    if (LST_Enqueue(list, e) != LST_NORMAL)
	return 0;

    return APP_NORMAL;
}
