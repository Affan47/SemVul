buildIndexMap(const VertexBoneAssignmentList& boneAssignments,
        IndexMap& boneIndexToBlendIndexMap, IndexMap& blendIndexToBoneIndexMap)
    {
        if (boneAssignments.empty())
        {

            boneIndexToBlendIndexMap.clear();
            blendIndexToBoneIndexMap.clear();
            return;
        }

        typedef set<unsigned short>::type BoneIndexSet;
        BoneIndexSet usedBoneIndices;


        VertexBoneAssignmentList::const_iterator itVBA, itendVBA;
        itendVBA = boneAssignments.end();
        for (itVBA = boneAssignments.begin(); itVBA != itendVBA; ++itVBA)
        {
            usedBoneIndices.insert(itVBA->second.boneIndex);
        }


        blendIndexToBoneIndexMap.resize(usedBoneIndices.size());
        boneIndexToBlendIndexMap.resize(*usedBoneIndices.rbegin() + 1);


        BoneIndexSet::const_iterator itBoneIndex, itendBoneIndex;
        unsigned short blendIndex = 0;
        itendBoneIndex = usedBoneIndices.end();
        for (itBoneIndex = usedBoneIndices.begin(); itBoneIndex != itendBoneIndex; ++itBoneIndex, ++blendIndex)
        {
            boneIndexToBlendIndexMap[*itBoneIndex] = blendIndex;
            blendIndexToBoneIndexMap[blendIndex] = *itBoneIndex;
        }
    }
