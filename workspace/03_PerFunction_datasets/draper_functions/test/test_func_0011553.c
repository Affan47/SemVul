Format(const wxLongLong& size, bool add_bytes_suffix, enum CSizeFormat::_format format, bool thousands_separator, int num_decimal_places)
{
	return CSizeFormatBase::Format(COptions::Get(), size, add_bytes_suffix, format, thousands_separator, num_decimal_places);
}
