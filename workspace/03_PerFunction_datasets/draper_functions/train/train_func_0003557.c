get_phase (double tempK) const throw ()
{
	if (data.boiling_point.has_value ())
	{
		if (data.boiling_point.value <= tempK)
			return Phase::GAS;
		else if (data.melting_point.has_value () &&
				data.melting_point.value <= tempK)
			return Phase::LIQUID;
		else
			return Phase::SOLID;
	}
	else if (data.melting_point.has_value ())
	{
		if (data.melting_point.value <= tempK)
			return Q_UNK;
		else
			return Phase::SOLID;
	}
	else
		return Q_UNK;
}
