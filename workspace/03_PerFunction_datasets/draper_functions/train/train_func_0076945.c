et_get_n_selections (AtkText *text)
{
	EText *etext;
	GObject *obj =  atk_gobject_accessible_get_object (ATK_GOBJECT_ACCESSIBLE (text));

	if (obj == NULL)
		return -1;
	etext = E_TEXT (obj);

	if (etext->selection_start !=
	    etext->selection_end)
		return 1;
	return 0;
}
