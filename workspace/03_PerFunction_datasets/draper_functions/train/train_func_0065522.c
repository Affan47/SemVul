showMessage (QString text, QLightDM::Greeter::MessageType type)
{
    status_notify ("%s SHOW-MESSAGE TEXT=\"%s\"", greeter_id, text.toAscii ().constData ());
}
