update_from_control_for_size (GthTestSimple  *self,
			      GError        **error)
{
	GthOpData op_data;
	double    value;
	guint64   size;

	op_data = int_op_data[gtk_combo_box_get_active (GTK_COMBO_BOX (self->priv->size_op_combo_box))];
	self->priv->op = op_data.op;
	self->priv->negative = op_data.negative;

	value = atol (gtk_entry_get_text (GTK_ENTRY (self->priv->text_entry)));
	size = value * size_data[gtk_combo_box_get_active (GTK_COMBO_BOX (self->priv->size_combo_box))].size;
	gth_test_simple_set_data_as_size (self, size);

	if ((self->priv->data.i == 0) && (self->priv->op == GTH_TEST_OP_LOWER)) {
		if (error != NULL)
			*error = g_error_new (GTH_TEST_ERROR, 0, _("The test definition is incomplete"));
		return FALSE;
	}

	return TRUE;
}
