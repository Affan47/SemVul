mdiobb_reset(struct mii_bus *bus)
{
	struct mdiobb_ctrl *ctrl = bus->priv;
	if (ctrl->reset)
		ctrl->reset(bus);
	return 0;
}
