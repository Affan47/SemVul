rid() const
{
	if (banked()) {
		return _rid + _bank_offset;
	}

	return _rid;
}
