gmpc_meta_watcher_data_changed (GmpcMetaWatcher * self, mpd_Song * song, MetaDataType type, MetaDataResult result, MetaData * met)
{
#line 214 "gmpc-meta-watcher.c"
	GValue ___param_values[5];
	GValue ___return_val;

memset (&___return_val, 0, sizeof (___return_val));
memset (&___param_values, 0, sizeof (___param_values));

#line 40 "gmpc-meta-watcher.gob"
	g_return_if_fail (self != NULL);
#line 40 "gmpc-meta-watcher.gob"
	g_return_if_fail (GMPC_IS_META_WATCHER (self));
#line 225 "gmpc-meta-watcher.c"

	___param_values[0].g_type = 0;
	g_value_init (&___param_values[0], G_TYPE_FROM_INSTANCE (self));
	g_value_set_instance (&___param_values[0], (gpointer) self);

	___param_values[1].g_type = 0;
	g_value_init (&___param_values[1], G_TYPE_POINTER);
	g_value_set_pointer (&___param_values[1], (gpointer ) song);

	___param_values[2].g_type = 0;
	g_value_init (&___param_values[2], G_TYPE_INT);
	g_value_set_int (&___param_values[2], (gint ) type);

	___param_values[3].g_type = 0;
	g_value_init (&___param_values[3], G_TYPE_INT);
	g_value_set_int (&___param_values[3], (gint ) result);

	___param_values[4].g_type = 0;
	g_value_init (&___param_values[4], G_TYPE_POINTER);
	g_value_set_pointer (&___param_values[4], (gpointer ) met);

	g_signal_emitv (___param_values,
		object_signals[DATA_CHANGED_SIGNAL],
		0 ,
		&___return_val);

	g_value_unset (&___param_values[0]);
	g_value_unset (&___param_values[1]);
	g_value_unset (&___param_values[2]);
	g_value_unset (&___param_values[3]);
	g_value_unset (&___param_values[4]);
}
