snd_hdac_i915_init_bpo(struct hdac_bus *bus)
{
	struct component_match *match = NULL;
	struct device *dev = bus->dev;
	struct i915_audio_component *acomp;
	int ret;

	acomp = kzalloc(sizeof(*acomp), GFP_KERNEL);
	if (!acomp)
		return -ENOMEM;
	bus->audio_component = acomp;
	hdac_acomp = acomp;

	component_match_add(dev, &match, hdac_component_master_match_bpo, bus);
	ret = component_master_add_with_match(dev, &hdac_component_master_ops,
					      match);
	if (ret < 0)
		goto out_err;


	request_module("i915_bpo");

	if (!acomp->ops) {
		ret = -ENODEV;
		goto out_master_del;
	}
	dev_dbg(dev, "bound to i915_bpo component master\n");

	return 0;
out_master_del:
	component_master_del(dev, &hdac_component_master_ops);
out_err:
	kfree(acomp);
	bus->audio_component = NULL;
	dev_err(dev, "failed to add i915_bpo component master (%d)\n", ret);

	return ret;
}
