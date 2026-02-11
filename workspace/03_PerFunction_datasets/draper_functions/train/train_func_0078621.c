handle_ruleset_tech(const struct packet_ruleset_tech *p)
{
  struct advance *a = advance_by_number(p->id);

  fc_assert_ret_msg(NULL != a, "Bad advance %d.", p->id);

  names_set(&a->name, p->name, p->rule_name);
  sz_strlcpy(a->graphic_str, p->graphic_str);
  sz_strlcpy(a->graphic_alt, p->graphic_alt);
  a->require[AR_ONE] = advance_by_number(p->req[AR_ONE]);
  a->require[AR_TWO] = advance_by_number(p->req[AR_TWO]);
  a->require[AR_ROOT] = advance_by_number(p->root_req);
  a->flags = p->flags;
  a->preset_cost = p->preset_cost;
  a->num_reqs = p->num_reqs;
  PACKET_STRVEC_EXTRACT(a->helptext, p->helptext);

  tileset_setup_tech_type(tileset, a);
}
