clip_copy_selection(clip)
    VimClipboard	*clip;
{
    if (VIsual_active && (State & NORMAL) && clip->available)
    {
	clip_update_selection(clip);
	clip_free_selection(clip);
	clip_own_selection(clip);
	if (clip->owned)
	    clip_get_selection(clip);
	clip_gen_set_selection(clip);
    }
}
