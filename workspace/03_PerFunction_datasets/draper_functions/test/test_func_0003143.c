print_text_field_set(PrintWindow *pw, TextInfo field, gboolean active)
{
	if (active)
		{
		pw->text_fields |= field;
		}
	else
		{
		pw->text_fields &= ~field;
		}

	print_window_layout_render(pw);
}
