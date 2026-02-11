IoMessage_locals_durationArgAt_(IoMessage *self, void *locals, int n)
{
	IoObject *v = IoMessage_locals_valueArgAt_(self, (IoObject *)locals, n);
	if (!ISDURATION(v)) IoMessage_locals_numberArgAt_errorForType_(self, (IoObject *)locals, n, "Duration");
	return v;
}
