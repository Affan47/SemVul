set(PropertyReceiver* receiver, const String& value)
{
	if (!value.empty())
	{
		static_cast<Window*>(receiver)->setMouseCursor(PropertyHelper::stringToImage(value));
	}
}
