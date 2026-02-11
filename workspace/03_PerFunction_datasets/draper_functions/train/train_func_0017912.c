pci_hp_create_module_link(struct pci_slot *pci_slot)
{
	struct hotplug_slot *slot = pci_slot->hotplug;
	struct kobject *kobj = NULL;
	int ret;

	if (!slot || !slot->ops)
		return;
	kobj = kset_find_obj(module_kset, slot->ops->mod_name);
	if (!kobj)
		return;
	ret = sysfs_create_link(&pci_slot->kobj, kobj, "module");
	if (ret)
		dev_err(&pci_slot->bus->dev, "Error creating sysfs link (%d)\n",
			ret);
	kobject_put(kobj);
}
