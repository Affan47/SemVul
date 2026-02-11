_multicast_publish(jdns_session_t *s, int mode, const jdns_rr_t *rr)
{
	mdnsdr r;
	published_item_t *pub;
	int next_id;
	jdns_event_t *event;
	int n;

	r = 0;
	next_id = get_next_req_id(s);


	pub = 0;
	for(n = 0; n < s->published->count; ++n)
	{
		published_item_t *i = (published_item_t *)s->published->item[n];
		if(i->qtype == rr->type && jdns_domain_cmp(i->qname, rr->owner))
		{
			pub = i;
			break;
		}
	}
	if(pub)
		goto error;

	if(!jdns_rr_verify(rr))
		goto error;

	if(mode == JDNS_PUBLISH_UNIQUE)
		r = mdnsd_unique(s->mdns, (char *)rr->owner, rr->type, rr->ttl, _multicast_pubresult, s);
	else
		r = mdnsd_shared(s->mdns, (char *)rr->owner, rr->type, rr->ttl);

	if(!_publish_applyrr(s, r, rr))
		goto error;

	pub = published_item_new();
	pub->id = next_id;
	pub->mode = mode;
	pub->qname = _ustrdup(rr->owner);
	pub->qtype = rr->type;
	pub->rec = r;
	pub->rr = jdns_rr_copy(rr);
	list_insert(s->published, pub, -1);


	if(mode == JDNS_PUBLISH_SHARED)
		report_published(s, pub);

	return pub->id;

error:
	_debug_line(s, "attempt to publish record, malformed, unsupported, or duplicate type");

	if(r)
	{

		mdnsd_done(s->mdns, r);
	}


	event = jdns_event_new();
	event->type = JDNS_EVENT_PUBLISH;
	event->id = next_id;
	event->status = JDNS_STATUS_ERROR;
	_append_event_and_hold_id(s, event);

	return next_id;
}
