get_what(void)
{
    int	bogus_from = ToggleGet(save_widgets.bogus_from_toggle);
    int	bogus_subj = ToggleGet(save_widgets.bogus_subj_toggle);
    int	head       = ToggleGet(save_widgets.head_toggle);
    int	body       = ToggleGet(save_widgets.body_toggle);
    int	empty      = ToggleGet(save_widgets.empty_toggle);
    int	what = 0;

    if (bogus_from)
	what |= SAVE_BOGUS_FROM;
    if (bogus_subj)
	what |= SAVE_BOGUS_SUBJ;
    if (head)
	what |= SAVE_HEAD;
    if (body)
	what |= SAVE_BODY;
    if (empty)
	what |= SAVE_EMPTY;

    return what;
}
