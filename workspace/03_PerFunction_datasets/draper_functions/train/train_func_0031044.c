cb_scg_direction_changed (SheetControlGUI *scg)
{

	int i = scg->active_panes;
	while (i-- > 0) {
		GnmPane *pane = scg->pane[i];
		if (NULL != pane)
			gnm_pane_set_direction (scg->pane[i],
			                        scg_sheet (scg)->text_is_rtl? GOC_DIRECTION_RTL: GOC_DIRECTION_LTR);
	}
	scg_resize (scg, TRUE);
}
