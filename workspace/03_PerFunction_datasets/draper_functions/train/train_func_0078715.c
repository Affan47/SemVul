calloc_tspi(TSS_HCONTEXT tspContext, UINT32 howMuch)
{
	struct memTable *table = NULL;
	struct memEntry *newEntry = NULL;

	MUTEX_LOCK(memtable_lock);

	table = getTable(tspContext);
	if (table == NULL) {
		if ((table = __tspi_createTable()) == NULL) {
			MUTEX_UNLOCK(memtable_lock);
			return NULL;
		}
		table->tspContext = tspContext;
		__tspi_addTable(table);
	}

	newEntry = calloc(1, sizeof(struct memEntry));
	if (newEntry == NULL) {
		LogError("malloc of %zd bytes failed.", sizeof(struct memEntry));
		MUTEX_UNLOCK(memtable_lock);
		return NULL;
	}

	newEntry->memPointer = calloc(1, howMuch);
	if (newEntry->memPointer == NULL) {
		LogError("malloc of %d bytes failed.", howMuch);
		free(newEntry);
		MUTEX_UNLOCK(memtable_lock);
		return NULL;
	}


	__tspi_addEntry(tspContext, newEntry);

	MUTEX_UNLOCK(memtable_lock);

	return newEntry->memPointer;
}
