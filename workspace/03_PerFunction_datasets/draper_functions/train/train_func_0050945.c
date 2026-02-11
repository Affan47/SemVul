IoDuration_compare(IoDuration *self, IoDuration *other)
{
	if (ISDURATION(other))
	{
	return Duration_compare(DATA(self), DATA(other));
	}

	return IoObject_defaultCompare(self, other);
}
