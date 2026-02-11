fill_can_switch_to_government_array(struct player* plr, bool* can_switch)
{
  governments_iterate(gov) {


    can_switch[government_index(gov)] = can_change_to_government(plr, gov);
  } governments_iterate_end;
}
