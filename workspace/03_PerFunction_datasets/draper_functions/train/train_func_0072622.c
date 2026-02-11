kernel26_power_supply_finalize (GObject* obj) {
	Kernel26PowerSupply * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, KERNEL26_TYPE_POWER_SUPPLY, Kernel26PowerSupply);
	_g_object_unref0 (self->priv->subsystem);
	_g_free0 (self->priv->sysfsnode);
	_g_free0 (self->name);
	_g_free0 (self->typ);
	G_OBJECT_CLASS (kernel26_power_supply_parent_class)->finalize (obj);
}
