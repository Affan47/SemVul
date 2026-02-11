sys_check_sepcount (const int *list, int n)
{
    int i, ns = 0;
    int err = 0;

    for (i=1; i<=list[0]; i++) {
	if (list[i] == LISTSEP) {
	    ns++;
	}
    }

    if (ns != n - 1) {
	err = E_ARGS;
    }

    return err;
}
