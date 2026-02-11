dbalign(Vmalloc_t * vm, size_t size, size_t align)
#else
static Void_t *dbalign(vm, size, align)
Vmalloc_t *vm;
size_t size;
size_t align;
#endif
{
    reg Vmuchar_t *data;
    reg size_t s;
    reg char *file;
    reg int line;
    reg Vmdata_t *vd = vm->data;

    VMFILELINE(vm, file, line);

    if (size <= 0 || align <= 0)
	return NIL(Void_t *);

    if (!(vd->mode & VM_TRUST)) {
	if (ISLOCK(vd, 0))
	    return NIL(Void_t *);
	SETLOCK(vd, 0);
    }

    if ((s = ROUND(size, ALIGN) + DB_EXTRA) < sizeof(Body_t))
	s = sizeof(Body_t);

    if (!
	(data = (Vmuchar_t *) KPVALIGN(vm, s, align, (*(Vmbest->alignf)))))
	goto done;

    data += DB_HEAD;
    dbsetinfo(data, size, file, line);

    if ((vd->mode & VM_TRACE) && _Vmtrace) {
	vm->file = file;
	vm->line = line;
	(*_Vmtrace) (vm, NIL(Vmuchar_t *), data, size, align);
    }

  done:
    CLRLOCK(vd, 0);
    return (Void_t *) data;
}
