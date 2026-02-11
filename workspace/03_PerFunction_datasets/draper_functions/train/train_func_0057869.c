initialize(ErrorHandler *errh)
{
  ElementCastTracker filter(router(), "Storage");
  if (router()->visit_downstream(this, 0, &filter) < 0)
    return errh->error("flow-based router context failure");
  _queue_elements = filter.elements();
  click_chatter("Unqueue2: found %d downstream queues", _queue_elements.size());
  _packets = 0;
  ScheduleInfo::initialize_task(this, &_task, errh);
  return 0;
}
