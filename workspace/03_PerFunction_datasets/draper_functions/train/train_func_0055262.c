ApplyUniqueIndices(FCDGeometryMesh* targMesh, FCDGeometryMesh* baseMesh, const UInt32List& newIndices, const FCDGeometryIndexTranslationMapList& translationMaps)
	{
		uint32 largest = 0;
		const FCDGeometryIndexTranslationMap* aMap = translationMaps[0];
		for (FCDGeometryIndexTranslationMap::const_iterator it = aMap->begin(), itEnd = aMap->end(); it != itEnd; ++it)
		{
			const UInt32List& curList = it->second;
			for (UInt32List::const_iterator uit = curList.begin(); uit != curList.end(); ++uit)
			{
				largest = max(largest, *uit);
			}
		}

		uint32 newBufferLen = largest + 1;

		for (size_t i = 0; i < targMesh->GetSourceCount(); i++)
		{
			FCDGeometrySource* targSource = targMesh->GetSource(i);
			for (size_t j = 0; j < baseMesh->GetSourceCount(); j++)
			{


				FCDGeometrySource* baseSource = baseMesh->GetSource(j);
				if (baseSource->GetType() == targSource->GetType())
				{
					const FCDGeometryIndexTranslationMap* translationMap = translationMaps[j];
					ApplyUniqueIndices(targSource, newBufferLen, translationMap);
				}
			}

			targMesh->AddVertexSource(targSource);
		}


		const uint32* newIdxPtr = newIndices.begin();
		size_t nNewIndices = newIndices.size();
		for (size_t p = 0; p < targMesh->GetPolygonsCount(); p++)
		{
			FCDGeometryPolygons* polygons = targMesh->GetPolygons(p);
			FCDGeometryPolygonsInput* anInput = polygons->GetInput(0);
			size_t nIndices = anInput->GetIndexCount();

			FUAssert(nIndices >= nNewIndices, nIndices = nNewIndices);
			anInput->SetIndices(newIdxPtr, nIndices);

			newIdxPtr += nIndices;
			nNewIndices -= nIndices;
		}
	}
