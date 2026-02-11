IoRegex_cloneWithOptions_(IoRegex *self, int options)
{
	IoRegex *clone = 0;

	if (options == DATA(self)->options)
		return self;

	clone = IOCLONE(self);
	DATA(clone)->options = options;
	return clone;
}
