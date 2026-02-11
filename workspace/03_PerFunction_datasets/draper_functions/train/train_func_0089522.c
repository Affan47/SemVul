IoMessage_copy_(IoMessage *self, IoMessage *other)
{
	IoMessage_rawSetName_(self, DATA(other)->name);

	{
		List *l1 = DATA(self)->args;
		List *l2 = DATA(other)->args;
		int i, max = List_size(l2);
		List_removeAll(l1);

		for (i = 0; i < max; i ++)
		{
			List_append_(l1, IOREF(List_rawAt_(l2, i)));
		}
	}

	IoMessage_rawSetNext_(self, DATA(other)->next);
	IoMessage_rawSetCachedResult_(self, DATA(other)->cachedResult);
	IoMessage_rawCopySourceLocation(self, other);
}
