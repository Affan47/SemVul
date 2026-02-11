economy_report_dialog_popdown(void)
{
  if(pEconomyDlg) {
    if (pEconomy_Sell_Dlg) {
       del_group_of_widgets_from_gui_list(pEconomy_Sell_Dlg->pBeginWidgetList,
			      pEconomy_Sell_Dlg->pEndWidgetList);
       FC_FREE(pEconomy_Sell_Dlg);
    }
    popdown_window_group_dialog(pEconomyDlg->pBeginWidgetList,
					    pEconomyDlg->pEndWidgetList);
    FC_FREE(pEconomyDlg->pScroll);
    FC_FREE(pEconomyDlg);
    set_wstate(get_tax_rates_widget(), FC_WS_NORMAL);
    widget_redraw(get_tax_rates_widget());
    widget_mark_dirty(get_tax_rates_widget());
  }
}
