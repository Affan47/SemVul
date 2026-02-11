nv50_bar_dtor(struct nvkm_bar *base)
{
	struct nv50_bar *bar = nv50_bar(base);
	nvkm_gpuobj_del(&bar->bar1);
	nvkm_vm_ref(NULL, &bar->bar1_vm, bar->pgd);
	nvkm_gpuobj_del(&bar->bar3);
	if (bar->bar3_vm) {
		nvkm_memory_del(&bar->bar3_vm->pgt[0].mem[0]);
		nvkm_vm_ref(NULL, &bar->bar3_vm, bar->pgd);
	}
	nvkm_gpuobj_del(&bar->pgd);
	nvkm_gpuobj_del(&bar->pad);
	nvkm_gpuobj_del(&bar->mem);
	return bar;
}
