is_button_toggled(
	FvwmWindow *fw, int button)
{
	mwm_flags mf;

	if (!HAS_MWM_BUTTONS(fw))
	{
		return False;
	}
	mf = TB_MWM_DECOR_FLAGS(GetDecor(fw, buttons[button]));
	if ((mf & MWM_DECOR_MAXIMIZE) && IS_MAXIMIZED(fw))
	{
		return True;
	}
	if ((mf & MWM_DECOR_SHADE) && IS_SHADED(fw))
	{
		return True;
	}
	if ((mf & MWM_DECOR_STICK) &&
	    (IS_STICKY_ACROSS_PAGES(fw) || IS_STICKY_ACROSS_DESKS(fw)))
	{
		return True;
	}
	if (TB_FLAGS(fw->decor->buttons[button]).has_layer &&
	    fw->layer == TB_LAYER(fw->decor->buttons[button]))
	{
		return True;
	}

	return False;
}
