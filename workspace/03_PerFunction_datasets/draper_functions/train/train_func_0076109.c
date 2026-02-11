e_cell_popup_do_popup (ECellPopupView *ecp_view,
                       GdkEvent *event,
                       gint row,
                       gint view_col)
{
	ECellPopup *ecp = E_CELL_POPUP (ecp_view->cell_view.ecell);
	gint (*popup_func) (ECellPopup *ecp, GdkEvent *event, gint row, gint view_col);

	ecp->popup_cell_view = ecp_view;

	popup_func = E_CELL_POPUP_CLASS (G_OBJECT_GET_CLASS (ecp))->popup;

	ecp->popup_view_col = view_col;
	ecp->popup_row = row;
	ecp->popup_model = ((ECellView *) ecp_view)->e_table_model;

	return popup_func ? popup_func (ecp, event, row, view_col) : FALSE;
}
