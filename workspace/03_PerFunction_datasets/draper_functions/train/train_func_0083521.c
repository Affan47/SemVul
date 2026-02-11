reinit_one_web (web, reg)
     struct web *web;
     rtx reg;
{
  web->old_color = web->color + 1;
  init_one_web_common (web, reg);
  web->span_deaths = 0;
  web->spill_temp = 0;
  web->orig_spill_temp = 0;
  web->use_my_regs = 0;
  web->spill_cost = 0;
  web->was_spilled = 0;
  web->is_coalesced = 0;
  web->artificial = 0;
  web->live_over_abnormal = 0;
  web->mode_changed = 0;
  web->move_related = 0;
  web->in_load = 0;
  web->target_of_spilled_move = 0;
  web->num_aliased = 0;
  if (web->type == PRECOLORED)
    {
      web->num_defs = 0;
      web->num_uses = 0;
      web->orig_spill_cost = 0;
    }
  CLEAR_HARD_REG_SET (web->bias_colors);
  CLEAR_HARD_REG_SET (web->prefer_colors);
  web->reg_rtx = NULL;
  web->stack_slot = NULL;
  web->pattern = NULL;
  web->alias = NULL;
  if (web->moves)
    abort ();
  if (!web->useless_conflicts)
    abort ();
}
