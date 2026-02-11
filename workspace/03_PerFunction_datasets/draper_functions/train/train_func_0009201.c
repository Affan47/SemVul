createMesh(io::IReadFile* file)
	{
		scene::IMesh* m = createCSMMesh(file);

		if (!m)
			return 0;

		SAnimatedMesh* am = new SAnimatedMesh();
		am->Type = EAMT_CSM;
		am->addMesh(m);
		m->drop();

		am->recalculateBoundingBox();
		return am;
	}
