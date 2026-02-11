cast(const char *n)
{
    if (strcmp(n, "NotifierQueue") == 0)
	return (NotifierQueue *)this;
    else if (strcmp(n, Notifier::EMPTY_NOTIFIER) == 0)
	return static_cast<Notifier *>(&_empty_note);
    else
	return SimpleQueue::cast(n);
}
