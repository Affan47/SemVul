unitdisband_callback_yes(Widget w, XtPointer client_data, XtPointer call_data)
{
  struct unit_list *punits = client_data;


  if (!can_client_issue_orders()) {
    unit_list_destroy(punits);
    return;
  }

  unit_list_iterate(punits, punit) {
    if (!unit_has_type_flag(punit, F_UNDISBANDABLE)) {
      request_unit_disband(punit);
    }
  } unit_list_iterate_end;

  unit_list_destroy(punits);
  destroy_message_dialog(w);
}
