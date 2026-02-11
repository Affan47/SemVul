suggest_tech_exchange(struct player* player1,
                                  struct player* player2)
{
  int worth[advance_count()];
  bool is_dangerous;

  worth[A_NONE] = 0;

  advance_index_iterate(A_FIRST, tech) {
    if (player_invention_state(player1, tech) == TECH_KNOWN) {
      if (player_invention_state(player2, tech) != TECH_KNOWN
          && player_invention_reachable(player2, tech, FALSE)) {
        worth[tech] = -compute_tech_sell_price(player1, player2, tech,
	                                       &is_dangerous);
	if (is_dangerous) {

	  worth[tech] = 0;
	}
      } else {
        worth[tech] = 0;
      }
    } else {
      if (player_invention_state(player2, tech) == TECH_KNOWN
          && player_invention_reachable(player1, tech, FALSE)) {
        worth[tech] = compute_tech_sell_price(player2, player1, tech,
	                                      &is_dangerous);
	if (is_dangerous) {

	  worth[tech] = 0;
	}
      } else {
        worth[tech] = 0;
      }
    }
  } advance_index_iterate_end;

  advance_index_iterate(A_FIRST, tech) {
    if (worth[tech] <= 0) {
      continue;
    }
    advance_index_iterate(A_FIRST, tech2) {
      int diff;

      if (worth[tech2] >= 0) {
        continue;
      }

      diff = worth[tech] + worth[tech2];
      if ((diff > 0 && player1->economic.gold >= diff)
          || (diff < 0 && player2->economic.gold >= -diff)
	  || diff == 0) {
        ai_diplomacy_suggest(player1, player2, CLAUSE_ADVANCE, tech2);
	ai_diplomacy_suggest(player2, player1, CLAUSE_ADVANCE, tech);
	if (diff > 0) {
	  ai_diplomacy_suggest(player1, player2, CLAUSE_GOLD, diff);
	} else if (diff < 0) {
	  ai_diplomacy_suggest(player2, player1, CLAUSE_GOLD, -diff);
	}
	return;
      }
    } advance_index_iterate_end;
  } advance_index_iterate_end;
}
