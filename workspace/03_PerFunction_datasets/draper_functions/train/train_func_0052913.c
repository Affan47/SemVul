deformvertexes_bulge( f32 dt, SModifierFunction &function )
{
	function.func = SINUS;
	function.wave = core::reciprocal( function.bulgewidth );

	dt *= function.bulgespeed * 0.1f;
	const f32 phase = function.phase;

	const u32 vsize = Original->Vertices.size();
	for ( u32 i = 0; i != vsize; ++i )
	{
		const video::S3DVertex2TCoords &src = Original->Vertices[i];
		video::S3DVertex &dst = MeshBuffer->Vertices[i];

		const f32 wavephase = (Original->Vertices[i].TCoords.X ) * function.wave;
		function.phase = phase + wavephase;

		const f32 f = function.evaluate( dt );

		if ( 0 == function.count )
			dst.Pos = src.Pos - MeshOffset;

		dst.Pos.X += f * src.Normal.X;
		dst.Pos.Y += f * src.Normal.Y;
		dst.Pos.Z += f * src.Normal.Z;

		if ( i == 0 )
			MeshBuffer->BoundingBox.reset ( dst.Pos );
		else
			MeshBuffer->BoundingBox.addInternalPoint ( dst.Pos );
	}

	function.count = 1;
}
