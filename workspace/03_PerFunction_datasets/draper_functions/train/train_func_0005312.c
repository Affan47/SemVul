compare_icon(icon_t *icon1, icon_t *icon2) {
	int different = 0;
	if(!different &&
	   ((icon1->id != icon2->id) ||
	   (icon1->width != icon2->width) ||
	   (icon1->height != icon2->height)))
		different = 1;
	if(!different &&
	   ((icon1->lvc.version != icon2->lvc.version) ||
	   (icon1->lvc.characts != icon2->lvc.characts)))
		different = 1;
	return different;
}
