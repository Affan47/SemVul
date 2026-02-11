WriteMaterial(FCDObject* object, xmlNode* parentNode)
{
	FCDMaterial* material = (FCDMaterial*)object;

	xmlNode* materialNode = FArchiveXML::WriteToEntityXMLFCDEntity(material, parentNode, DAE_MATERIAL_ELEMENT);


	xmlNode* instanceEffectNode = AddChild(materialNode, DAE_INSTANCE_EFFECT_ELEMENT);
	if (material->GetEffect() != NULL)
	{
		const FUUri& uri = material->GetEffectReference()->GetUri();
		fstring uriString = material->GetDocument()->GetFileManager()->CleanUri(uri);
		AddAttribute(instanceEffectNode, DAE_URL_ATTRIBUTE, uriString);


		for (FCDMaterialTechniqueHintList::iterator itH = material->GetTechniqueHints().begin(); itH != material->GetTechniqueHints().end(); ++itH)
		{
			xmlNode* hintNode = AddChild(instanceEffectNode, DAE_FXCMN_HINT_ELEMENT);
			AddAttribute(hintNode, DAE_PLATFORM_ATTRIBUTE, (*itH).platform);
			AddAttribute(hintNode, DAE_REF_ATTRIBUTE, (*itH).technique);
		}


		size_t parameterCount = material->GetEffectParameterCount();
		for (size_t p = 0; p < parameterCount; ++p)
		{
			FArchiveXML::LetWriteObject(material->GetEffectParameter(p), instanceEffectNode);
		}
	}
	else
	{
		AddAttribute(instanceEffectNode, DAE_URL_ATTRIBUTE, fm::string("#"));
	}

	FArchiveXML::WriteEntityExtra(material, materialNode);
	return materialNode;
}
