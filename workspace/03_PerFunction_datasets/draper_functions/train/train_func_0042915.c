see_combat(struct unit *pattacker, struct unit *pdefender)
{
  struct packet_unit_short_info unit_att_short_packet, unit_def_short_packet;
  struct packet_unit_info unit_att_packet, unit_def_packet;


  package_short_unit(pattacker, &unit_att_short_packet,
		     UNIT_INFO_IDENTITY, 0, FALSE);
  package_short_unit(pdefender, &unit_def_short_packet,
		     UNIT_INFO_IDENTITY, 0, FALSE);
  package_unit(pattacker, &unit_att_packet);
  package_unit(pdefender, &unit_def_packet);

  conn_list_iterate(game.est_connections, pconn) {
    struct player *pplayer = pconn->playing;

    if (pplayer != NULL) {


      if (map_is_known_and_seen(unit_tile(pattacker), pplayer, V_MAIN)
          || map_is_known_and_seen(unit_tile(pdefender), pplayer,
                                   V_MAIN)) {


        if (pplayer == unit_owner(pattacker)) {
          send_packet_unit_info(pconn, &unit_att_packet);
        } else {
          send_packet_unit_short_info(pconn,
                                      &unit_att_short_packet);
        }

        if (pplayer == unit_owner(pdefender)) {
          send_packet_unit_info(pconn, &unit_def_packet);
        } else {
          send_packet_unit_short_info(pconn,
                                      &unit_def_short_packet);
        }
      }
    } else if (pconn->observer) {

      send_packet_unit_info(pconn, &unit_att_packet);
      send_packet_unit_info(pconn, &unit_def_packet);
    }
  } conn_list_iterate_end;
}
