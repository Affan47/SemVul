List_do_(List *self, ListDoCallback *callback)
{
	LIST_FOREACH(self, i, v, if (v) (*callback)(v));
}
