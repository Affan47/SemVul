snd_pcm_mmap_status_fault(struct vm_area_struct *area,
						struct vm_fault *vmf)
{
	struct snd_pcm_substream *substream = area->vm_private_data;
	struct snd_pcm_runtime *runtime;

	if (substream == NULL)
		return VM_FAULT_SIGBUS;
	runtime = substream->runtime;
	vmf->page = virt_to_page(runtime->status);
	get_page(vmf->page);
	return 0;
}
