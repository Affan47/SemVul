mouse_captured(UI_GADGET *gadget)
{
	if (!gadget)
		gadget = this;

	return (my_wnd->mouse_captured_gadget == gadget);
}
