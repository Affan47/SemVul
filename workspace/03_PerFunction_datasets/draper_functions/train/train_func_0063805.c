AttachChilds_Anim(int iParentID,aiNode* piParent, AnimBoneList& bones,const aiNodeAnim** node_anims)
{
	ai_assert(NULL != piParent && !piParent->mNumChildren);


	for (int i = 0; i < (int)bones.size();++i)	{
		if (iParentID != i && bones[i].mParentIndex == iParentID)	{
			++piParent->mNumChildren;
		}
	}
	if (piParent->mNumChildren)	{
		piParent->mChildren = new aiNode*[piParent->mNumChildren];
		for (int i = 0; i < (int)bones.size();++i)	{

			if (iParentID != i && bones[i].mParentIndex == iParentID)
			{
				aiNode* pc;

				*piParent->mChildren++ = pc = new aiNode();
				pc->mName = aiString(bones[i].mName);
				pc->mParent = piParent;


				const aiNodeAnim** cur = node_anims;
				while ((**cur).mNodeName != pc->mName)++cur;

				aiMatrix4x4::Translation((**cur).mPositionKeys[0].mValue,pc->mTransformation);
				pc->mTransformation = pc->mTransformation * aiMatrix4x4((**cur).mRotationKeys[0].mValue.GetMatrix()) ;


				AttachChilds_Anim( i, pc, bones,node_anims);
			}
		}

		piParent->mChildren -= piParent->mNumChildren;
	}
}
