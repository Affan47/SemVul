set_keyboard_focus (NemoIconContainer *container,
		    NemoIcon *icon)
{
	g_assert (icon != NULL);

	if (icon == container->details->keyboard_focus) {
		return;
	}

	clear_keyboard_focus (container);

	container->details->keyboard_focus = icon;

	eel_canvas_item_set (EEL_CANVAS_ITEM (container->details->keyboard_focus->item),
			       "highlighted_as_keyboard_focus", 1,
			       NULL);

	emit_atk_focus_tracker_notify (icon);
}
