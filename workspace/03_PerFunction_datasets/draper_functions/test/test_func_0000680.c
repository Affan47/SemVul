setPosition(int pos)
{
	int len;

	if (!entry)
		return;

	len = length();

	if (pos < 0)
		pos = 0;
	else if (pos >= len)
		pos = -1;

	gtk_editable_set_position(GTK_EDITABLE(entry), pos);
}
