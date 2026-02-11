chat_push_topic(const char *topic)
{
	if (topic_stack_slot < CHAT_TOPIC_STACK_SIZE - 1) {
		topic_stack[++topic_stack_slot] = strdup(topic);
	} else {
		ErrorMessage(__FUNCTION__,
			     "The maximum depth of %hd topics has been maxed out.",
			     PLEASE_INFORM, IS_WARNING_ONLY, CHAT_TOPIC_STACK_SIZE);
	}
}
