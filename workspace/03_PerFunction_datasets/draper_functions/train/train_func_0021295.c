paging_on_lm(void *pml)
{
	if (!cpu_id.fid.bits.pae)
		return;
	__asm__ __volatile__(

		"movl %0, %%cr3\n\t"

		"movl %%cr0, %%eax\n\t"
		"orl $0x80000000, %%eax\n\t"
		"movl %%eax, %%cr0\n\t"
		:
		: "r" (pml)
		: "ax"
		);
}
