really_diplomacy_cancel_meeting(struct player *pplayer,
					    struct player *pother)
{
  struct Treaty *ptreaty = find_treaty(pplayer, pother);

  if (ptreaty) {
    dlsend_packet_diplomacy_cancel_meeting(pother->connections,
					   player_number(pplayer),
					   player_number(pplayer));
    notify_player(pother, NULL, E_DIPLOMACY, ftc_server,
                  _("%s canceled the meeting!"),
                  player_name(pplayer));

    dlsend_packet_diplomacy_cancel_meeting(pplayer->connections,
					   player_number(pother),
					   player_number(pplayer));
    notify_player(pplayer, NULL, E_DIPLOMACY, ftc_server,
                  _("Meeting with %s canceled."),
                  player_name(pother));
    treaty_list_remove(treaties, ptreaty);
    clear_treaty(ptreaty);
    free(ptreaty);
  }
}
