au_dy_fin(void)
{
	int i;

	for (i = 0; i < AuDyLast; i++)
		WARN_ON(!list_empty(&dynop[i].head));
}
