init(const HeightMap &hm, f32 scale, colour_func cf, IVideoDriver *driver)
	{
		Scale = scale;

		const u32 mp = driver -> getMaximalPrimitiveCount();
		Width = hm.width();
		Height = hm.height();

		const u32 sw = mp / (6 * Height);

		u32 i=0;
		for(u32 y0 = 0; y0 < Height; y0 += sw)
		{
			u16 y1 = y0 + sw;
			if (y1 >= Height)
				y1 = Height - 1;
			addstrip(hm, cf, y0, y1, i);
			++i;
		}
		if (i<Mesh->getMeshBufferCount())
		{

			for (u32 j=i; j<Mesh->getMeshBufferCount(); ++j)
			{
				Mesh->getMeshBuffer(j)->drop();
			}
			Mesh->MeshBuffers.erase(i,Mesh->getMeshBufferCount()-i);
		}

		Mesh->recalculateBoundingBox();
	}
