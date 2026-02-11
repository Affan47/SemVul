intel_th_free(struct intel_th *th)
{
	int i;

	intel_th_request_hub_module_flush(th);
	for (i = 0; i < TH_SUBDEVICE_MAX; i++)
		if (th->thdev[i] != th->hub)
			intel_th_device_remove(th->thdev[i]);

	intel_th_device_remove(th->hub);

	__unregister_chrdev(th->major, 0, TH_POSSIBLE_OUTPUTS,
			    "intel_th/output");

	ida_simple_remove(&intel_th_ida, th->id);

	kfree(th);
}
