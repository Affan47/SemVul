lookup(HASH_TABLE *table, KEY name, size_t createSize)
{
	size_t i;
	if (table->size == 0) {
		if (!createSize)
			return 0;
		table->v = calloc(INIT_SIZE, sizeof(NAMED *));
		if (!table->v)
			return 0;
		table->size = INIT_SIZE;
		table->usedLim = INIT_SIZE / 2;
		i = hash(name) & (table->size - 1);
	} else {
		unsigned long h = hash(name);
		for (i = h & (table->size - 1);
			table->v[i]; i == 0 ? i = table->size - 1 : --i) {
			if (keyeq(name, table->v[i]->name))
				return table->v[i];
		}
		if (!createSize)
			return 0;
		if (table->used == table->usedLim) {

			size_t newSize = table->size * 2;
			NAMED **newV = calloc(newSize, sizeof(NAMED *));
			if (!newV)
				return 0;
			for (i = 0; i < table->size; i++)
				if (table->v[i]) {
					size_t j;
					for (j = hash(table->v[i]->
							name) & (newSize - 1);
						newV[j];
						j == 0 ? j =
						newSize - 1 : --j) ;
					newV[j] = table->v[i];
				}
			free(table->v);
			table->v = newV;
			table->size = newSize;
			table->usedLim = newSize / 2;
			for (i = h & (table->size - 1);
				table->v[i];
				i == 0 ? i = table->size - 1 : --i) ;
		}
	}
	table->v[i] = calloc(1, createSize);
	if (!table->v[i])
		return 0;
	table->v[i]->name = name;
	(table->used)++;
	return table->v[i];
}
