Clone(FCDEffectProfile* _clone) const
{
	FCDEffectProfileFX* clone = NULL;
	if (_clone == NULL) { _clone = clone = new FCDEffectProfileFX(const_cast<FCDocument*>(GetDocument()), const_cast<FCDEffect*>(GetParent())); }
	else if (_clone->GetObjectType() == FCDEffectProfileFX::GetClassType()) clone = (FCDEffectProfileFX*) _clone;

	if (_clone != NULL) FCDEffectProfile::Clone(_clone);
	if (clone != NULL)
	{
		clone->type = type;


		clone->codes.reserve(codes.size());
		for (const FCDEffectCode** itC = codes.begin(); itC != codes.end(); ++itC)
		{
			FCDEffectCode* clonedCode = clone->AddCode();
			(*itC)->Clone(clonedCode);
		}


		clone->techniques.reserve(techniques.size());
		for (const FCDEffectTechnique** itT = techniques.begin(); itT != techniques.end(); ++itT)
		{
			FCDEffectTechnique* clonedTechnique = clone->AddTechnique();
            (*itT)->Clone(clonedTechnique);
		}
	}

	return _clone;
}
