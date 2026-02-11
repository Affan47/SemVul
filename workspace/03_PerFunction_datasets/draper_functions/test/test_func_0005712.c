SPI_copytuple(HeapTuple tuple)
{
	MemoryContext oldcxt = NULL;
	HeapTuple	ctuple;

	if (tuple == NULL)
	{
		SPI_result = SPI_ERROR_ARGUMENT;
		return NULL;
	}

	if (_SPI_curid + 1 == _SPI_connected)
	{
		if (_SPI_current != &(_SPI_stack[_SPI_curid + 1]))
			elog(ERROR, "SPI stack corrupted");
		oldcxt = MemoryContextSwitchTo(_SPI_current->savedcxt);
	}

	ctuple = heap_copytuple(tuple);

	if (oldcxt)
		MemoryContextSwitchTo(oldcxt);

	return ctuple;
}
