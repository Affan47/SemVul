GetAnimatedFloat(FCDGeometryInstance* geometryInstance, FCDMaterial* material, const fm::string& semantic)
	{


		if (material == NULL) return NULL;
		FCDEffect* effect = material->GetEffect();
		if (effect == NULL) return NULL;
		FCDEffectProfile* effectProfile = effect->FindProfile(FUDaeProfileType::COMMON);
		if (effectProfile == NULL) return NULL;
		FCDEffectStandard* effectStandard = (FCDEffectStandard*) effectProfile;
		bool isFloat = true;


		FCDEffectParameter* effectStandardParam = effectStandard->GetParam(semantic, &isFloat);
		if (!effectStandardParam) return NULL;
		const fm::string& reference = effectStandardParam->GetReference();
		if (reference.empty())
		{
			if (isFloat) return &(((FCDEffectParameterFloat*)effectStandardParam)->GetValue());
			else return NULL;
		}
		FCDEffectParameter* geometryParam = geometryInstance != NULL ? FindEffectParameterBySemantic(geometryInstance, semantic) : NULL;
		FCDEffectParameter* materialParam = FindEffectParameterByReference(material, reference, true);
		FCDEffectParameter* effectParam = FindEffectParameterByReference(effect, reference, true);
		FCDEffectParameter* effectProfileParam = FindEffectParameterByReference(effectProfile, reference, false);

		if (isFloat)
		{
			if (geometryParam)
			{
				if (geometryParam->GetType() != FCDEffectParameter::FLOAT) return NULL;
				else return &((FCDEffectParameterFloat*)geometryParam)->GetValue();
			}

			else if (materialParam)
			{
				if (materialParam->GetType() != FCDEffectParameter::FLOAT) return NULL;
				else return &((FCDEffectParameterFloat*)materialParam)->GetValue();
			}
			else if (effectParam)
			{
				if (effectParam->GetType() != FCDEffectParameter::FLOAT) return NULL;
				else return &((FCDEffectParameterFloat*)effectParam)->GetValue();
			}
			else if (effectProfileParam)
			{
				if (effectProfileParam->GetType() != FCDEffectParameter::FLOAT) return NULL;
				else return &((FCDEffectParameterFloat*)effectProfileParam)->GetValue();
			}
			else return &((FCDEffectParameterFloat*)effectStandardParam)->GetValue();
		}
		else return NULL;
	}
