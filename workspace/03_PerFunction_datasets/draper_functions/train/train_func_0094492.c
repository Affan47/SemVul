se200pci_cont_enum_put(struct snd_kcontrol *kc,
				  struct snd_ctl_elem_value *uc)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kc);
	struct se_spec *spec = ice->spec;
	int n = kc->private_value;
	unsigned int vol1;

	vol1 = uc->value.enumerated.item[0];
	if (vol1 >= se200pci_get_enum_count(n))
		return -EINVAL;
	if (spec->vol[n].ch1 != vol1) {
		spec->vol[n].ch1 = vol1;
		se200pci_cont_update(ice, n);
		return 1;
	}
	return 0;
}
