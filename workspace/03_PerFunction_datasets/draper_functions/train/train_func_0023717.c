ReadSourceInterpolation(xmlNode* sourceNode, UInt32List& array)
	{
		if (sourceNode != NULL)
		{

			xmlNode* accessorNode = FindTechniqueAccessor(sourceNode);
			uint32 count = ReadNodeCount(accessorNode);
			array.resize(count);


			uint32 stride = ReadNodeStride(accessorNode);
			StringList stringArray(count * stride);
			xmlNode* arrayNode = FindChildByType(sourceNode, DAE_NAME_ARRAY_ELEMENT);
			const char* arrayContent = ReadNodeContentDirect(arrayNode);
			FUStringConversion::ToStringList(arrayContent, stringArray);
			for (uint32 i = 0; i < count; ++i)
			{
				array[i] = (uint32) FUDaeInterpolation::FromString(stringArray[i * stride]);
			}
		}
	}
