spin_change(GtkSpinButton *spinbutton,gSpinBox *data)
{
	data->selectAll();
	if (data->onChange) data->onChange(data);
}
