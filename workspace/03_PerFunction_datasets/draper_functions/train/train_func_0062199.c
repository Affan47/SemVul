cast(const char *n)
{
    if (strcmp(n, class_name()) == 0)
	return static_cast<Element *>(this);
    else if (strcmp(n, Notifier::EMPTY_NOTIFIER) == 0)
	return static_cast<Notifier *>(this);
    else
	return 0;
}
