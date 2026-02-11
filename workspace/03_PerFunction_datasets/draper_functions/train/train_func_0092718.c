startElement(StartElementEvent *event)
{
  ElementNode::add(*grove_, *event);
  delete event;
}
