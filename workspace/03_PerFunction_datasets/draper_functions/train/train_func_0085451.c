do_pageup()
{
	if (active_wordlist_item==0)
		return;
	if (!wordlist_head[0].enable)
		return;
	on_shooting_wordlistitem_active (0);
	wordlist_item[0].active = true;
	wordlist_item[0].draw ();
}
