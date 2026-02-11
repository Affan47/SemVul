g_auto_pointer_copy(GAuto *auto_ptr)
{
	AutoPointer	*ptr;
	AutoPointerRef	*ref;
	AutoPointer	*newp;

	if (auto_ptr == NULL)
		return NULL;

	ptr = auto_ptr;
	ref = ptr->ref;
	newp = g_new0(AutoPointer, 1);

	newp->ref = ref;
	newp->ptr = ref->pointer;
	++(ref->cnt);

#ifdef REF_DEBUG
	G_PRINT_REF ("XXXX COPY(%lx) -- REF (%d)\n", ref->pointer, ref->cnt);
#endif
	return newp;
}
