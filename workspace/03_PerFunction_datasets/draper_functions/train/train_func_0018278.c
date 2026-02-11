createCurvedSurface_nosubdivision(SMeshBufferLightMap* meshBuffer,
					s32 faceIndex,
					s32 patchTesselation,
					s32 storevertexcolor)
{
	tBSPFace * face = &Faces[faceIndex];
	u32 j,k,m;


	const u32 controlWidth = face->size[0];
	const u32 controlHeight = face->size[1];
	if ( 0 == controlWidth || 0 == controlHeight )
		return;

	video::S3DVertex2TCoords v;

	m = meshBuffer->Vertices.size();
	meshBuffer->Vertices.reallocate(m+controlHeight * controlWidth);
	for ( j = 0; j!= controlHeight * controlWidth; ++j )
	{
		copy( &v, &Vertices [ face->vertexIndex + j ], storevertexcolor );
		meshBuffer->Vertices.push_back( v );
	}

	meshBuffer->Indices.reallocate(meshBuffer->Indices.size()+6*(controlHeight-1) * (controlWidth-1));
	for ( j = 0; j!= controlHeight - 1; ++j )
	{
		for ( k = 0; k!= controlWidth - 1; ++k )
		{
			meshBuffer->Indices.push_back( m + k + 0 );
			meshBuffer->Indices.push_back( m + k + controlWidth + 0 );
			meshBuffer->Indices.push_back( m + k + controlWidth + 1 );

			meshBuffer->Indices.push_back( m + k + 0 );
			meshBuffer->Indices.push_back( m + k + controlWidth + 1 );
			meshBuffer->Indices.push_back( m + k + 1 );
		}
		m += controlWidth;
	}
}
