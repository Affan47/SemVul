recv_ruleset_effect_req(const struct packet_ruleset_effect_req *packet)
{
  if (packet->effect_id != effect_list_size(ruleset_cache.tracker) - 1) {
    log_error("Bug in recv_ruleset_effect_req.");
  } else {
    struct effect *peffect = effect_list_get(ruleset_cache.tracker, -1);
    struct requirement req, *preq;

    req = req_from_values(packet->source_type, packet->range, packet->survives,
	packet->negated, packet->source_value);

    preq = fc_malloc(sizeof(*preq));
    *preq = req;

    effect_req_append(peffect, packet->neg, preq);
  }
}
