Clone(FCDEffectParameterSurfaceInit* _clone) const
{
	FCDEffectParameterSurfaceInitFrom* clone = NULL;
	if (_clone == NULL) clone = new FCDEffectParameterSurfaceInitFrom();
	else if (_clone->GetInitType() == GetInitType()) clone = (FCDEffectParameterSurfaceInitFrom*) _clone;

	if (_clone != NULL) FCDEffectParameterSurfaceInit::Clone(_clone);
	if (clone != NULL)
	{
		clone->face = face;
		clone->mip = mip;
		clone->slice = slice;
	}
	return clone;
}
