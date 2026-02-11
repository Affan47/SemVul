append_to(XML_Attribute *queue) {
    if (!queue) return this;
    queue->next = append_to(queue->next);
    return queue;
}
