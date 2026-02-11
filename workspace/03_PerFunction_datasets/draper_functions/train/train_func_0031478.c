send_ruleset_team_names(struct conn_list *dest)
{
  struct packet_team_name_info team_name_info_p;

  team_slots_iterate(tslot) {
    const char *name = team_slot_defined_name(tslot);

    if (NULL == name) {

      break;
    }

    team_name_info_p.team_id = team_slot_index(tslot);
    sz_strlcpy(team_name_info_p.team_name, name);

    lsend_packet_team_name_info(dest, &team_name_info_p);
  } team_slots_iterate_end;
}
