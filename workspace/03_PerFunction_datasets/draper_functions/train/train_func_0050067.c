delete_closure_free (gpointer data)
{
	DeleteClosure *closure = data;
	if (closure->service)
		g_object_unref (closure->service);
	g_variant_unref (closure->attributes);
	g_clear_object (&closure->cancellable);
	g_slice_free (DeleteClosure, closure);
}
