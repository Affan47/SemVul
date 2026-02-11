dai_unit_init(struct unit *punit)
{


  struct unit_ai *unit_data = fc_calloc(1, sizeof(struct unit_ai));

  unit_data->done = FALSE;
  unit_data->cur_pos = NULL;
  unit_data->prev_pos = NULL;
  unit_data->target = 0;
  BV_CLR_ALL(unit_data->hunted);
  unit_data->ferryboat = 0;
  unit_data->passenger = 0;
  unit_data->bodyguard = 0;
  unit_data->charge = 0;

  unit_set_ai_data(punit, default_ai_get_self(), unit_data);
}
