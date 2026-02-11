OnEvent(const SEvent& event)
	{

		if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
		{
			switch (event.KeyInput.Key)
			{
			case irr::KEY_KEY_W:
				Terrain->setMaterialFlag(video::EMF_WIREFRAME,
						!Terrain->getMaterial(0).Wireframe);
				Terrain->setMaterialFlag(video::EMF_POINTCLOUD, false);
				return true;
			case irr::KEY_KEY_P:
				Terrain->setMaterialFlag(video::EMF_POINTCLOUD,
						!Terrain->getMaterial(0).PointCloud);
				Terrain->setMaterialFlag(video::EMF_WIREFRAME, false);
				return true;
			case irr::KEY_KEY_D:
				Terrain->setMaterialType(
					Terrain->getMaterial(0).MaterialType == video::EMT_SOLID ?
					video::EMT_DETAIL_MAP : video::EMT_SOLID);
				return true;
			case irr::KEY_KEY_S:
				showBox=!showBox;
				Skybox->setVisible(showBox);
				Skydome->setVisible(!showBox);
				return true;
			case irr::KEY_KEY_X:
				showDebug=!showDebug;
				Terrain->setDebugDataVisible(showDebug?scene::EDS_BBOX_ALL:scene::EDS_OFF);
				return true;
			default:
				break;
			}
		}

		return false;
	}
