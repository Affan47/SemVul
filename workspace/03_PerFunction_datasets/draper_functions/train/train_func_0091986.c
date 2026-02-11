get_widget(const char *name)
{
#ifdef G_DISABLE_ASSERT
	return GTK_WIDGET(get_object(name));
#else
	GObject *object = get_object(name);

	if (!GTK_IS_WIDGET(object))
	{
		fprintf(stderr, "Scope: object %s is not a widget\n", name);
		abort();
	}

	return GTK_WIDGET(object);
#endif
}
