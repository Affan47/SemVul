handle_edit_city_remove(struct connection *pc, int id)
{
  struct city *pcity;

  pcity = game_city_by_number(id);
  if (pcity == NULL) {
    notify_conn(pc->self, NULL, E_BAD_COMMAND, ftc_editor,
                _("No such city (ID %d)."), id);
    return;
  }

  remove_city(pcity);
}
