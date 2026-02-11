set(PropertyReceiver* receiver, const String& value)
{
    static_cast<Window*>(receiver)->setYPosition(PropertyHelper::stringToUDim(value));
}
