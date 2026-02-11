IoList_slice(IoList *self, IoObject *locals, IoMessage *m)
{


	List *list;
	int start, end;

		IoList_sliceArguments(self, locals, m, &start, &end);

		if (end < start)
		{
				return IoList_new(IOSTATE);
		}
		else
		{
			list = List_cloneSlice(DATA(self), start, end);
			return IoList_newWithList_(IOSTATE, list);
		}
}
