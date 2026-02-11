file_changed(BW *bw,int c,B *b,int *notify)
{
	if (mkqw(bw->parent, sz(joe_gettext(_("Notice: File on disk changed! (hit ^C to continue)  "))), file_changed, NULL, b, notify)) {
		b->gave_notice = 1;
		return 0;
	} else
		return -1;
}
