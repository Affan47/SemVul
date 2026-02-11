iounmap(volatile void __iomem *addr)
{
	struct vm_struct *p, *o;

	if ((void __force *)addr <= high_memory)
		return;


	if ((void __force *)addr >= phys_to_virt(ISA_START_ADDRESS) &&
	    (void __force *)addr < phys_to_virt(ISA_END_ADDRESS))
		return;

	addr = (volatile void __iomem *)
		(PAGE_MASK & (unsigned long __force)addr);

	mmiotrace_iounmap(addr);


	p = find_vm_area((void __force *)addr);

	if (!p) {
		printk(KERN_ERR "iounmap: bad address %p\n", addr);
		dump_stack();
		return;
	}

	free_memtype(p->phys_addr, p->phys_addr + get_vm_area_size(p));


	o = remove_vm_area((void __force *)addr);
	BUG_ON(p != o || o == NULL);
	kfree(p);
}
