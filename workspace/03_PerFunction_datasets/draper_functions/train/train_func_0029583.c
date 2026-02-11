on_filter_modulo (GObject *object,
                  gpointer user_data)
{
	guint value = mock_object_value (object);
	guint *modulo = user_data;

	g_assert (modulo != NULL);
	g_assert_cmpuint (value, >=, 0);
	g_assert_cmpuint (value, <, NUM_OBJECTS);

	return (value % *modulo) == 0;
}
