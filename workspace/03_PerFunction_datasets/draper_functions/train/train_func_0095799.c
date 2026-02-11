Clone(FCDEffectParameterSurfaceInit* clone) const
{
	if (clone == NULL)
	{
		clone = FCDEffectParameterSurfaceInitFactory::Create(GetInitType());
		return clone != NULL ? Clone(clone) : NULL;
	}
	else
	{

		return clone;
	}
}
