HandlePubsubEventMessage(
    const buzz::XmlElement* pubsub_event) {
  ASSERT(pubsub_event->Name() == QN_PUBSUB_EVENT);
  for (const buzz::XmlChild* child = pubsub_event->FirstChild();
       child != NULL;
       child = child->NextChild()) {
    const buzz::XmlElement* child_element = child->AsElement();
    const buzz::QName& child_name(child_element->Name());
    if (child_name == QN_PUBSUB_EVENT_ITEMS) {
      HandlePubsubItems(child_element);
    }
  }
}
