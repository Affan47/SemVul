create_20k1_hw_obj(struct hw **rhw)
{
	struct hw20k1 *hw20k1;

	*rhw = NULL;
	hw20k1 = kzalloc(sizeof(*hw20k1), GFP_KERNEL);
	if (!hw20k1)
		return -ENOMEM;

	spin_lock_init(&hw20k1->reg_20k1_lock);
	spin_lock_init(&hw20k1->reg_pci_lock);

	hw20k1->hw = ct20k1_preset;

	*rhw = &hw20k1->hw;

	return 0;
}
