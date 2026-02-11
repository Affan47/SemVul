ReadPoseVertices(Pose *pose)
{
	if (!AtEnd())
	{
		uint16_t id = ReadHeader();
		while (!AtEnd() && id == M_POSE_VERTEX)
		{
			Pose::Vertex v;
			v.index = Read<uint32_t>();
			ReadVector(v.offset);
			if (pose->hasNormals)
				ReadVector(v.normal);

			pose->vertices[v.index] = v;

			if (!AtEnd())
				id = ReadHeader();
		}
		if (!AtEnd())
			RollbackHeader();
	}
}
