WriteEffectParameter(FCDObject* object, xmlNode* parentNode)
{
	FCDEffectParameter* effectParameter = (FCDEffectParameter*)object;

	xmlNode* parameterNode;
	if (effectParameter->IsGenerator())
	{
		parameterNode = AddChild(parentNode, DAE_FXCMN_NEWPARAM_ELEMENT);
		AddAttribute(parameterNode, DAE_SID_ATTRIBUTE, effectParameter->GetReference());
	}
	else if (effectParameter->IsModifier())
	{
		parameterNode = AddChild(parentNode, DAE_FXCMN_SETPARAM_ELEMENT);
		AddAttribute(parameterNode, DAE_REF_ATTRIBUTE, effectParameter->GetReference());
	}
	else
	{
		parameterNode = AddChild(parentNode, DAE_PARAMETER_ELEMENT);
		if (!effectParameter->GetReference().empty() && !effectParameter->IsReferencer())
		{
			AddAttribute(parameterNode, DAE_SID_ATTRIBUTE, effectParameter->GetReference());
		}
	}


	for (size_t i = 0; i < effectParameter->GetAnnotationCount(); ++i)
	{
		FCDEffectParameterAnnotation* annotation = effectParameter->GetAnnotation(i);
		xmlNode* annotateNode = AddChild(parameterNode, DAE_ANNOTATE_ELEMENT);
		AddAttribute(annotateNode, DAE_NAME_ATTRIBUTE, *annotation->name);
		switch ((uint32) annotation->type)
		{
		case FCDEffectParameter::BOOLEAN: AddChild(annotateNode, DAE_FXCMN_BOOL_ELEMENT, *annotation->value); break;
		case FCDEffectParameter::STRING: AddChild(annotateNode, DAE_FXCMN_STRING_ELEMENT, *annotation->value); break;
		case FCDEffectParameter::INTEGER: AddChild(annotateNode, DAE_FXCMN_INT_ELEMENT, *annotation->value); break;
		case FCDEffectParameter::FLOAT: AddChild(annotateNode, DAE_FXCMN_FLOAT_ELEMENT, *annotation->value); break;
		default: break;
		}
	}

	if (!effectParameter->IsAnimator())
	{

		if (effectParameter->IsGenerator() && !effectParameter->GetSemantic().empty())
		{
			AddChild(parameterNode, DAE_FXCMN_SEMANTIC_ELEMENT, effectParameter->GetSemantic());
		}
	}
	return parameterNode;
}
