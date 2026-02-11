UArray_removeLastPathComponent(UArray *self)
{
	UArray seps = UArray_stackAllocedWithCString_(IO_PATH_SEPARATORS);
	long pos = UArray_findLastPathComponent(self);
	if (pos) pos --;
	UArray_setSize_(self, pos);
}
