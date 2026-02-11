x86_64_is_kvaddr(ulong addr)
{
	if (machdep->flags & VM_XEN_RHEL4)
		return (addr >= VMALLOC_START);
	else
        	return (addr >= PAGE_OFFSET);
}
