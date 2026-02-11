lazyLoadTexture(int texID)
	{
		const bool mipmap = Driver->getTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS);
		Driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

		SpriteBank->setTexture(texID, Driver->getTexture( m_texture_files[texID].m_file_name ));

		Driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, mipmap);


		if (!SpriteBank->getTexture(texID))
		{
			return;
		}
		else
		{

			if (! m_texture_files[texID].m_has_alpha)
			{
				Driver->makeColorKeyTexture(SpriteBank->getTexture(texID), core::position2di(0,0));
			}
		}
	}
