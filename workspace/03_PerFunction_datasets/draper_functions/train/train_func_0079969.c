GetMaterialColor(const std::vector<PLY::PropertyInstance>& avList,
	unsigned int aiPositions[4],
	PLY::EDataType aiTypes[4],
	 aiColor4D* clrOut)
{
	ai_assert(NULL != clrOut);

	if (0xFFFFFFFF == aiPositions[0])clrOut->r = 0.0f;
	else
	{
		clrOut->r = NormalizeColorValue(avList[
			aiPositions[0]].avList.front(),aiTypes[0]);
	}

	if (0xFFFFFFFF == aiPositions[1])clrOut->g = 0.0f;
	else
	{
		clrOut->g = NormalizeColorValue(avList[
			aiPositions[1]].avList.front(),aiTypes[1]);
	}

	if (0xFFFFFFFF == aiPositions[2])clrOut->b = 0.0f;
	else
	{
		clrOut->b = NormalizeColorValue(avList[
			aiPositions[2]].avList.front(),aiTypes[2]);
	}


	if (0xFFFFFFFF == aiPositions[3])clrOut->a = 1.0f;
	else
	{
		clrOut->a = NormalizeColorValue(avList[
			aiPositions[3]].avList.front(),aiTypes[3]);
	}
}
