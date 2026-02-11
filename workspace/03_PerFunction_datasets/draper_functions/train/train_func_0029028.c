irmo_object_watch_destroy(IrmoObject *object,
					IrmoObjCallback func,
					void *user_data)
{
	irmo_return_val_if_fail(object != NULL, NULL);
	irmo_return_val_if_fail(func != NULL, NULL);

	return irmo_object_callback_watch_destroy(&object->callbacks,
                                                  func,
                                                  user_data);
}
