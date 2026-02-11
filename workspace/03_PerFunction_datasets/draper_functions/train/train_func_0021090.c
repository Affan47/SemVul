GetMaxExponent() const
{
	return STDMIN(GetSubgroupOrder()-1, Integer::Power2(2*DiscreteLogWorkFactor(GetFieldType()*GetModulus().BitCount())));
}
