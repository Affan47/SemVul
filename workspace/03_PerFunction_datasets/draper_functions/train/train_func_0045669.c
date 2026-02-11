calculateDistanceThresholds(bool scalechanged)
	{

		if (!OverrideDistanceThreshold)
		{
			TerrainData.LODDistanceThreshold.set_used(0);

			TerrainData.LODDistanceThreshold.reallocate(TerrainData.MaxLOD);

			const f64 size = TerrainData.PatchSize * TerrainData.PatchSize *
					TerrainData.Scale.X * TerrainData.Scale.Z;
			for (s32 i=0; i<TerrainData.MaxLOD; ++i)
			{
				TerrainData.LODDistanceThreshold.push_back(size * ((i+1+ i / 2) * (i+1+ i / 2)));
			}
		}
	}
