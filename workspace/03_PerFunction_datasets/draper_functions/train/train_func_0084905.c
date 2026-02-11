cast(const char *n)
{
    if (strcmp(n, "AggregateNotifier") == 0)
        return (AggregateNotifier *)this;
    else if (strcmp(n, "AggregateIPAddrPair") == 0)
	return (Element *)this;
    else
	return Element::cast(n);
}
