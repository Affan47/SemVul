gda_column_copy (GdaColumn *column)
{
	GdaColumn *column_copy;

	g_return_val_if_fail (GDA_IS_COLUMN (column), NULL);

	column_copy = gda_column_new ();
	column_copy->priv->defined_size = column->priv->defined_size;
	if (column->priv->id)
		column_copy->priv->id = g_strdup (column->priv->id);
	column_copy->priv->g_type = column->priv->g_type;
	column_copy->priv->allow_null = column->priv->allow_null;
	column_copy->priv->auto_increment = column->priv->auto_increment;
	column_copy->priv->auto_increment_start = column->priv->auto_increment_start;
	column_copy->priv->auto_increment_step = column->priv->auto_increment_step;
	column_copy->priv->position = column->priv->position;
	if (column->priv->default_value)
		column_copy->priv->default_value = gda_value_copy (column->priv->default_value);
	gda_attributes_manager_copy (_gda_column_attributes_manager, (gpointer) column, _gda_column_attributes_manager, (gpointer) column_copy);

	return column_copy;
}
