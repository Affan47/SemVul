add_entry()
{
  struct conn_data *data;

  data = xmalloc(sizeof(struct conn_data));

  data->count = opt.line->count;
  data->start_time = opt.line->time;
  if (opt.mode != REALTIME_RESPONSE) {
    data->end_time = 0;
  } else {
    data->end_time = opt.line->time;
  }
  data->hostname = xmalloc(strlen(opt.line->hostname) + 1);
  xstrncpy(data->hostname, opt.line->hostname, strlen(opt.line->hostname) + 1);
  data->chainlabel = xmalloc(strlen(opt.line->chainlabel) + 1);
  xstrncpy(data->chainlabel, opt.line->chainlabel, strlen(opt.line->chainlabel) + 1);
  data->branchname = xmalloc(strlen(opt.line->branchname) + 1);
  xstrncpy(data->branchname, opt.line->branchname, strlen(opt.line->branchname) + 1);
  data->interface = xmalloc(strlen(opt.line->interface) + 1);
  xstrncpy(data->interface, opt.line->interface, strlen(opt.line->interface) + 1);
  data->protocol = opt.line->protocol;
  data->datalen = opt.line->datalen;
  data->shost = opt.line->shost;
  data->sport = opt.line->sport;
  data->dhost = opt.line->dhost;
  data->dport = opt.line->dport;
  data->flags = opt.line->flags;
  data->id = opt.global_id++;

  data->next = first;
  first = data;
}
