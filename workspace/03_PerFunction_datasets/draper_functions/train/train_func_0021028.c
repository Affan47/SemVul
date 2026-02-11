fkt_record_irqs(fxt_t fxt, int fd)
	{
	struct code_list_item	*ptr;
	unsigned int i;

	write(fd, (void *)&fxt->nirqs, sizeof(fxt->nirqs));
	write(fd, (void *)&fxt->infos.ncpus, sizeof(fxt->infos.ncpus));
	for( ptr = fxt->irq_list;  ptr != NULL;  ptr = ptr->link )
		{
		write(fd, (void *)&ptr->code, sizeof(ptr->code));
		i = strlen(ptr->name)+1;
		write(fd, (void *)&i, sizeof(i));
		i = (i + 3) & ~3;
		write(fd, ptr->name, i);
		}
	return 0;
	}
