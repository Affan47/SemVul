city_can_buy(const struct city *pcity)
{


  return (can_client_issue_orders()
	  && NULL != pcity
	  && city_owner(pcity) == client.conn.playing
	  && pcity->turn_founded != game.info.turn
	  && !pcity->did_buy
	  && (VUT_UTYPE == pcity->production.kind
	     || !improvement_has_flag(pcity->production.value.building, IF_GOLD))
	  && !(VUT_UTYPE == pcity->production.kind
	      && pcity->anarchy != 0)
	  && city_production_buy_gold_cost(pcity) > 0);
}
