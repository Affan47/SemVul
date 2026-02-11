showMessage(const QString &message, const QString & id, int alignment)
{
	MessageThing * itemMessageThing = m_items.value(id);
	if (itemMessageThing == NULL) return;

	MessageThing * messageThing = new MessageThing;
	messageThing->alignment = alignment;
	messageThing->color = itemMessageThing->color;
	messageThing->rect = itemMessageThing->rect;;
	messageThing->message = message;
	m_messages.append(messageThing);
	repaint();
}
