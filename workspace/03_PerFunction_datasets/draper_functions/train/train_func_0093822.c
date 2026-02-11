emit(const String &str, void *user_data, bool more)
{
    if (_errh)
	return _errh->emit(str, user_data, more);
    else
	return ErrorHandler::emit(str, user_data, more);
}
