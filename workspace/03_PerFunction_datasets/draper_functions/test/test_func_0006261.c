completion_func(gpointer data)
{
	cm_return_val_if_fail(data != NULL, NULL);

	return ((completion_entry *)data)->string;
}
