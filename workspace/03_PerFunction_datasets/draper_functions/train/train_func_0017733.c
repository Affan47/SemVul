searchdrv(devp, list, max, isset)
CONST devinfo *devp, *list;
int max, isset;
{
	int i;

	for (i = 0; i < max; i++) {
		if (devp -> drive != list[i].drive) continue;
# ifdef	HDDMOUNT
		if (!list[i].cyl && isset) break;
# endif
		if (devp -> head == list[i].head
		&& devp -> sect == list[i].sect
		&& devp -> cyl == list[i].cyl
		&& !strpathcmp(devp -> name, list[i].name))
			break;
	}

	return(i);
}
