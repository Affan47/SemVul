find_callback_class(IrmoWorld *world,
                                             char *classname,
                                             IrmoClass **save_class)
{
        IrmoClass *klass;

	if (classname == NULL) {
		return &world->callbacks_all;
        }

	klass = irmo_interface_get_class(world->iface, classname);

	if (klass == NULL) {
		return NULL;
        }

        if (save_class != NULL) {
                *save_class = klass;
        }

	return &world->callbacks[klass->index];
}
