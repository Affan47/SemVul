cityrep_buy(struct city *pcity)
{
  int value;

  if (city_production_has_flag(pcity, IF_GOLD)) {
    create_event(pcity->tile, E_BAD_COMMAND, ftc_client,
                 _("You can't buy %s in %s!"),
                 improvement_name_translation(pcity->production.value.building),
                 city_link(pcity));
    return;
  }
  value = city_production_buy_gold_cost(pcity);

  if (city_owner(pcity)->economic.gold >= value) {
    city_buy_production(pcity);
  } else {

    char buf[MAX_LEN_MSG];


    fc_snprintf(buf, ARRAY_SIZE(buf), PL_("%s costs %d gold",
                                          "%s costs %d gold", value),
                city_production_name_translation(pcity),
                value);
    create_event(NULL, E_BAD_COMMAND, ftc_client,


                 PL_("%s and you only have %d gold.",
                     "%s and you only have %d gold.",
                     city_owner(pcity)->economic.gold),
                 buf, city_owner(pcity)->economic.gold);
  }
}
