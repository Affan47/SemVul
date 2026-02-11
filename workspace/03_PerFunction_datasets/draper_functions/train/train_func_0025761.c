GenerateVertexPackingMap(size_t maxIndex, size_t maxIndices, size_t maxVertices, const uint32* inIndices, uint16* outIndices, UInt16List* outPackingMap, uint16* outNVertices)
	{
		FUAssert(inIndices != NULL && outPackingMap != NULL, return 0);
		FUAssert(maxIndices < INVALID_VTX_IDX, maxIndices = INVALID_VTX_IDX - 1);
		outPackingMap->resize(maxIndex + 1, INVALID_VTX_IDX);
		uint16 nIndices, nVertices = 0;
		for (nIndices = 0; nIndices < maxIndices; ++nIndices)
		{
			if (outPackingMap->at(*inIndices) == INVALID_VTX_IDX)
			{

				outPackingMap->at(*inIndices) = nVertices;


				 if (++nVertices >= maxVertices) maxIndices = nIndices;
			}
			if (outIndices != NULL)
			{
				*outIndices = outPackingMap->at(*inIndices);
				++outIndices;
			}
			++inIndices;
		}

		FUAssert(nVertices <= nIndices, nVertices = nIndices);

		if (outNVertices != NULL) *outNVertices = nVertices;
		return nIndices;
	}
