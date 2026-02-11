setCurrentLODOfPatches(s32 lod)
	{
		const s32 count = TerrainData.PatchCount * TerrainData.PatchCount;
		for (s32 i=0; i< count; ++i)
			TerrainData.Patches[i].CurrentLOD = lod;
	}
