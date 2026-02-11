createMesh(io::IReadFile* file)
{
    if(!file)
        return 0;
    MeshFile = file;
    std::string filename=MeshFile->getFileName().c_str();
    Mesh = new scene::CM2Mesh();

	if ( load(true) )
    {
		for(u32 i=0;i<rootHeader.nGroups;i++)
        {
            char grpfilename[255];
            sprintf(grpfilename,"%s_%03u.wmo",filename.substr(0,filename.length()-4).c_str(),i);
            DEBUG(logdev("%s",grpfilename));
            MeshFile = io::IrrCreateIReadFileBasic(Device,grpfilename);
            if(!MeshFile)
            {
                logerror("Could not read file %s!",grpfilename);
                return 0;
            }
            load(false);
        }
    Mesh->updateBoundingBox();
    Device->getSceneManager()->getMeshManipulator()->flipSurfaces(Mesh);

    Device->getSceneManager()->getMeshManipulator()->recalculateNormals(Mesh,true);
    DEBUG(logdev("Complete Mesh contains a total of %u submeshes!",Mesh->getMeshBufferCount()));
	}
	else
	{
		Mesh->drop();
		Mesh = 0;
	}

	return Mesh;
}
