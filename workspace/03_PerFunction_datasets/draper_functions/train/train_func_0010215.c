getJointCount() const
{
	if (!Mesh || Mesh->getMeshType() != EAMT_SKINNED)
		return 0;

	ISkinnedMesh *skinnedMesh=(ISkinnedMesh*)Mesh;

	return skinnedMesh->getJointCount();
}
