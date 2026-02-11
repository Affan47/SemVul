gx_ir_edit_set_delay(GxIREdit *ir_edit, gint delay)
{
	g_return_if_fail(GX_IS_IR_EDIT(ir_edit));
	if (delay == gx_ir_edit_get_delay(ir_edit)) {
		return;
	}
	ir_edit_set_offset(ir_edit, max(delay, 0) - ir_edit->cutoff_low);
	gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
}
