removeMesh(const IMesh* const mesh)
{
	if ( !mesh )
		return;
	for (u32 i=0; i<Meshes.size(); ++i)
	{
		if (Meshes[i].Mesh && Meshes[i].Mesh->getMesh(0) == mesh)
		{
			Meshes[i].Mesh->drop();
			Meshes.erase(i);
			return;
		}
	}
}
