getNext(void *entry)
{
	unsigned long e=(unsigned long)entry;
	if (!e) return NULL;
	if (project && (e < project->count())) {
		return (void*)(e+1);
	} else {
		return NULL;
	}
}
