intel_th_populate(struct intel_th *th, struct resource *devres,
			     unsigned int ndevres, int irq)
{
	struct resource res[3];
	unsigned int req = 0;
	int i, err;


	for (i = 0; i < ARRAY_SIZE(intel_th_subdevices); i++) {
		struct intel_th_subdevice *subdev = &intel_th_subdevices[i];
		struct intel_th_device *thdev;
		int r;

		thdev = intel_th_device_alloc(th, subdev->type, subdev->name,
					      subdev->id);
		if (!thdev) {
			err = -ENOMEM;
			goto kill_subdevs;
		}

		memcpy(res, subdev->res,
		       sizeof(struct resource) * subdev->nres);

		for (r = 0; r < subdev->nres; r++) {
			int bar = TH_MMIO_CONFIG;


			if (!res[r].end && res[r].flags == IORESOURCE_MEM) {
				bar = res[r].start;
				res[r].start = 0;
				res[r].end = resource_size(&devres[bar]) - 1;
			}

			if (res[r].flags & IORESOURCE_MEM) {
				res[r].start	+= devres[bar].start;
				res[r].end	+= devres[bar].start;

				dev_dbg(th->dev, "%s:%d @ %pR\n",
					subdev->name, r, &res[r]);
			} else if (res[r].flags & IORESOURCE_IRQ) {
				res[r].start	= irq;
			}
		}

		err = intel_th_device_add_resources(thdev, res, subdev->nres);
		if (err) {
			put_device(&thdev->dev);
			goto kill_subdevs;
		}

		if (subdev->type == INTEL_TH_OUTPUT) {
			thdev->dev.devt = MKDEV(th->major, i);
			thdev->output.type = subdev->otype;
			thdev->output.port = -1;
		}

		err = device_add(&thdev->dev);
		if (err) {
			put_device(&thdev->dev);
			goto kill_subdevs;
		}


		if (subdev->type == INTEL_TH_SWITCH && !req) {
			th->hub = thdev;
			err = intel_th_request_hub_module(th);
			if (!err)
				req++;
		}

		th->thdev[i] = thdev;
	}

	return 0;

kill_subdevs:
	for (i-- ; i >= 0; i--)
		intel_th_device_remove(th->thdev[i]);

	return err;
}
