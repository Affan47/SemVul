gda_value_get_time (const GValue *value)
{
	g_return_val_if_fail (value, NULL);
	g_return_val_if_fail (gda_value_isa (value, GDA_TYPE_TIME), NULL);
	return (const GdaTime *) g_value_get_boxed(value);
}
