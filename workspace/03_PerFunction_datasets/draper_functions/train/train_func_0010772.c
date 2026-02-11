OnPublishResult(PubSubPublishTask* task) {
  const XmlElement* item = GetItemFromStanza(task->stanza());
  SignalPublishResult(this, task->task_id(), item);
}
