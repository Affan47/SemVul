help_overlay_maybe_blit(int overlay_id)
{
	Assert(overlay_id >= 0 && overlay_id < MAX_HELP_OVERLAYS);

	if ( Help_overlay_flags & (1<<overlay_id) ) {
		context_help_grey_screen();
		help_overlay_blit(overlay_id);
	}
}
