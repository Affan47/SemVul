read_proc_rs(void)
{
	FILE *fp;
	char buffer[256];
	struct proc_rs *p;
	struct proc_rs *list = NULL;
	int i = 0;

	errno = 0;
	if ((fp = fopen(PROC_RS_FILE, "r")) == NULL)
		return NULL;
	while (fgets(buffer, 256, fp) != NULL)
	{
		if (!i++) continue;
		if ((p = calloc(1, sizeof(struct proc_rs))) == NULL)
			break;
		safe_strncpy(p->dest_addr, strtok(buffer, " \t\n\r"), 10);
		safe_strncpy(p->dest_call, strtok(NULL, " \t\n\r"), 9);
		safe_strncpy(p->src_addr, strtok(NULL, " \t\n\r"), 10);
		safe_strncpy(p->src_call, strtok(NULL, " \t\n\r"), 9);
		safe_strncpy(p->dev,  strtok(NULL, " \t\n\r"), 13);
		p->lci   = safe_atox(strtok(NULL, " \t\n\r"));
		p->neigh = safe_atoi(strtok(NULL, " \t\n\r"));
		p->st    = safe_atoi(strtok(NULL, " \t\n\r"));
		p->vs    = safe_atoi(strtok(NULL, " \t\n\r"));
		p->vr    = safe_atoi(strtok(NULL, " \t\n\r"));
		p->va    = safe_atoi(strtok(NULL, " \t\n\r"));
		p->t     = safe_atoi(strtok(NULL, " \t\n\r"));
		p->t1    = safe_atoi(strtok(NULL, " \t\n\r"));
		p->t2    = safe_atoi(strtok(NULL, " \t\n\r"));
		p->t3    = safe_atoi(strtok(NULL, " \t\n\r"));
		p->hb    = safe_atoi(strtok(NULL, " \t\n\r"));
		p->sndq  = safe_atoi(strtok(NULL, " \t\n\r"));
		p->rcvq  = safe_atoi(strtok(NULL, " \t\n\r"));
		p->next  = list;
		list = p;
	}
	fclose(fp);
	return list;
}
