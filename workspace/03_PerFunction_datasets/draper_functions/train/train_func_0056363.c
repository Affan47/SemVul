LinkEffectStandard(FCDEffectStandard* effectStandard)
{
	FArchiveXML::LinkEffectProfile(effectStandard);


	FCDEffectParameterList parameters;
	size_t parameterCount = effectStandard->GetEffectParameterCount();
	for (size_t p = 0; p < parameterCount; ++p)
	{
		parameters.push_back(effectStandard->GetEffectParameter(p));
	}

	size_t parentParameterCount = effectStandard->GetParent()->GetEffectParameterCount();
	for (size_t p = 0; p < parentParameterCount; ++p)
	{
		parameters.push_back(effectStandard->GetParent()->GetEffectParameter(p));
	}


	for (uint32 i = 0; i < FUDaeTextureChannel::COUNT; ++i)
	{
		size_t bucketSize = effectStandard->GetTextureCount(i);
		for (size_t t = 0; t < bucketSize; ++t)
		{
			FArchiveXML::LinkTexture(effectStandard->GetTexture(i, t), parameters);
		}
	}
}
