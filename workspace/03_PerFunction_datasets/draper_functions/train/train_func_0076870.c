handle_diplomacy_remove_clause(int counterpart, int giver,
				    enum clause_type type, int value)
{
  struct Diplomacy_dialog *pdialog = find_diplomacy_dialog(counterpart);

  if (!pdialog) {
    return;
  }

  remove_clause(&pdialog->treaty, player_by_number(giver), type, value);
  update_diplomacy_dialog(pdialog);
  gui_dialog_alert(pdialog->dialog);
}
