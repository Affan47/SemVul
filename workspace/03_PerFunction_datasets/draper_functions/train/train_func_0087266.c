ParseLV4MeshBonesVertices(unsigned int iNumVertices,ASE::Mesh& mesh)
{
	AI_ASE_PARSER_INIT();
	mesh.mBoneVertices.resize(iNumVertices);
	while (true)
	{
		if ('*' == *filePtr)
		{
			++filePtr;


			if (TokenMatch(filePtr,"MESH_BONE_VERTEX" ,16))
			{

				unsigned int iIndex = strtoul10(filePtr,&filePtr);
				if (iIndex >= mesh.mPositions.size())
				{
					iIndex = (unsigned int)mesh.mPositions.size()-1;
					LogWarning("Bone vertex index is out of bounds. Using the largest valid "
						"bone vertex index instead");
				}


				float afVert[3];
				ParseLV4MeshFloatTriple(afVert);

				std::pair<int,float> pairOut;
				while (true)
				{

					if (!SkipSpaces(&filePtr))break;
					pairOut.first = strtoul10(filePtr,&filePtr);


					if (!SkipSpaces(&filePtr))break;
					filePtr = fast_atoreal_move<float>(filePtr,pairOut.second);


					if (-1 != pairOut.first)
					{
						mesh.mBoneVertices[iIndex].mBoneWeights.push_back(pairOut);
					}
				}
				continue;
			}
		}
		AI_ASE_HANDLE_SECTION("4","*MESH_BONE_VERTEX");
	}
	return;
}
