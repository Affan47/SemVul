LoadEffectParameterBool(FCDObject* object, xmlNode* parameterNode)
{
	if (!FArchiveXML::LoadEffectParameter(object, parameterNode)) return false;

	bool status = true;
	FCDEffectParameterBool* effectParameterBool = (FCDEffectParameterBool*)object;
	xmlNode* valueNode = FindChildByType(parameterNode, DAE_FXCMN_BOOL_ELEMENT);
	const char* valueString = ReadNodeContentDirect(valueNode);
	if (valueString == NULL || *valueString == 0)
	{

		FUError::Error(FUError::ERROR_LEVEL, FUError::ERROR_BAD_BOOLEAN_VALUE, parameterNode->line);
	}
	effectParameterBool->SetValue(FUStringConversion::ToBoolean(valueString));
	effectParameterBool->SetDirtyFlag();
	return status;
}
