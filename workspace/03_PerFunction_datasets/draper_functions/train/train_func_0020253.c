cloneBuffer( scene::SMeshBuffer *dest, const scene::SMeshBufferLightMap * buffer, bool translateCenter )
{
	dest->Material = buffer->Material;
	dest->Indices = buffer->Indices;

	const u32 vsize = buffer->Vertices.size();

	dest->Vertices.set_used( vsize );
	for ( u32 i = 0; i!= vsize; ++i )
	{
		const video::S3DVertex2TCoords& src = buffer->Vertices[i];
		video::S3DVertex &dst = dest->Vertices[i];

		dst.Pos = src.Pos;
		dst.Normal = src.Normal;
		dst.Color = 0xFFFFFFFF;
		dst.TCoords = src.TCoords;

		if ( i == 0 )
			dest->BoundingBox.reset ( src.Pos );
		else
			dest->BoundingBox.addInternalPoint ( src.Pos );
	}


	if ( translateCenter )
	{
		MeshOffset = dest->BoundingBox.getCenter();
		setPosition( MeshOffset );

		core::matrix4 m;
		m.setTranslation( -MeshOffset );
		SceneManager->getMeshManipulator()->transform( dest, m );
	}


	dest->Material.setTexture(0, (video::ITexture*) Shader);
}
