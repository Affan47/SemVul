mac_drv_get_space(struct s_smc *smc, unsigned int size)
{
	void *virt;

	pr_debug("mac_drv_get_space (%d bytes), ", size);
	virt = (void *) (smc->os.SharedMemAddr + smc->os.SharedMemHeap);

	if ((smc->os.SharedMemHeap + size) > smc->os.SharedMemSize) {
		printk("Unexpected SMT memory size requested: %d\n", size);
		return NULL;
	}
	smc->os.SharedMemHeap += size;

	pr_debug("mac_drv_get_space end\n");
	pr_debug("virt addr: %lx\n", (ulong) virt);
	pr_debug("bus  addr: %lx\n", (ulong)
	       (smc->os.SharedMemDMA +
		((char *) virt - (char *)smc->os.SharedMemAddr)));
	return virt;
}
