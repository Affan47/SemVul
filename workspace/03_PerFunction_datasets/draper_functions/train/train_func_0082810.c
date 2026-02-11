do_pageup ()
{
	int nowvalue = ((gint) ((GtkAdjustment *)wordlist_adjust)->value);
	if (nowvalue> 0)
	{
		nowvalue-= (gint) ((GtkAdjustment *)wordlist_adjust)->page_increment;
		if (nowvalue < 0)
			nowvalue = 0;
		((GtkAdjustment *) wordlist_adjust)->value = nowvalue;
		g_signal_emit_by_name (wordlist_adjust, "changed");
		on_test_wordlistadjust_valuechanged((GtkAdjustment *)wordlist_adjust,this);
	}
}
