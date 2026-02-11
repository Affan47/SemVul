hash_process(struct process *p)
{
	struct proc_hash_entry *phe;
	static char first_run = 1;


	if (first_run) {
		memset(proc_hash_table, 0, sizeof(struct proc_hash_entry) * 256);
		first_run = 0;
	}


	phe = &proc_hash_table[p->pid % 256];


	while (phe->next)
		phe = phe->next;


	phe->next = malloc(sizeof(struct proc_hash_entry));
	memset(phe->next, 0, sizeof(struct proc_hash_entry));
	phe->next->proc = p;
}
