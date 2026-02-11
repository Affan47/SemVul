videobuf_dvb_register_bus(struct videobuf_dvb_frontends *f,
			  struct module *module,
			  void *adapter_priv,
			  struct device *device,
			  short *adapter_nr,
			  int mfe_shared)
{
	struct list_head *list, *q;
	struct videobuf_dvb_frontend *fe;
	int res;

	fe = videobuf_dvb_get_frontend(f, 1);
	if (!fe) {
		printk(KERN_WARNING "Unable to register the adapter which has no frontends\n");
		return -EINVAL;
	}


	res = videobuf_dvb_register_adapter(f, module, adapter_priv, device,
		fe->dvb.name, adapter_nr, mfe_shared);
	if (res < 0) {
		printk(KERN_WARNING "videobuf_dvb_register_adapter failed (errno = %d)\n", res);
		return res;
	}


	mutex_lock(&f->lock);
	list_for_each_safe(list, q, &f->felist) {
		fe = list_entry(list, struct videobuf_dvb_frontend, felist);
		res = videobuf_dvb_register_frontend(&f->adapter, &fe->dvb);
		if (res < 0) {
			printk(KERN_WARNING "%s: videobuf_dvb_register_frontend failed (errno = %d)\n",
				fe->dvb.name, res);
			goto err;
		}
	}
	mutex_unlock(&f->lock);
	return 0;

err:
	mutex_unlock(&f->lock);
	videobuf_dvb_unregister_bus(f);
	return res;
}
