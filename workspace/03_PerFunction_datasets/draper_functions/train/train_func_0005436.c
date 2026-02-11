WriteEffectParameterFloat2(FCDObject* object, xmlNode* parentNode)
{
	FCDEffectParameterFloat2* effectParameterFloat2 = (FCDEffectParameterFloat2*)object;

	xmlNode* parameterNode = FArchiveXML::WriteEffectParameter(effectParameterFloat2, parentNode);
	FUSStringBuilder builder; builder.set(effectParameterFloat2->GetValue()->x); builder.append(' '); builder.append(effectParameterFloat2->GetValue()->y);
	AddChild(parameterNode, (effectParameterFloat2->GetFloatType() == FCDEffectParameterFloat2::FLOAT) ? DAE_FXCMN_FLOAT2_ELEMENT : DAE_FXCMN_HALF2_ELEMENT, builder);
	return parameterNode;
}
