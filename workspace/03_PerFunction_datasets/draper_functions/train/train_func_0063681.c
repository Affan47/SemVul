deformvertexes_autosprite( f32 dt, SModifierFunction &function )
{
	u32 vsize = Original->Vertices.size();
	u32 g;
	u32 i;

	const core::vector3df& camPos = SceneManager->getActiveCamera()->getPosition();

	video::S3DVertex * dv = MeshBuffer->Vertices.pointer();
	const video::S3DVertex2TCoords * vin = Original->Vertices.const_pointer();

	core::matrix4 lookat ( core::matrix4::EM4CONST_NOTHING );
	core::quaternion q;
	for ( i = 0; i < vsize; i += 4 )
	{

		core::vector3df center = 0.25f * ( vin[i+0].Pos + vin[i+1].Pos + vin[i+2].Pos + vin[i+3].Pos );
		core::vector3df forward = camPos - center;

		q.rotationFromTo ( vin[i].Normal, forward );
		q.getMatrixCenter ( lookat, center, MeshOffset );

		for ( g = 0; g < 4; ++g )
		{
			lookat.transformVect ( dv[i+g].Pos, vin[i+g].Pos );
			lookat.rotateVect ( dv[i+g].Normal, vin[i+g].Normal );
		}

	}
	function.count = 1;
}
