GetUnitWithBase(COptionsBase* pOptions, _unit unit, int base)
{
	_format format = _format(pOptions->GetOptionVal(OPTION_SIZE_FORMAT));
	if (base == 1000)
		format = si1000;
	else if (format != si1024)
		format = iec;
	return GetUnit(pOptions, unit, format);
}
