addSceneNode(ESCENE_NODE_TYPE type, ISceneNode* parent)
{
	switch(type)
	{
	case ESNT_CUBE:
		return Manager->addCubeSceneNode(10, parent);
	case ESNT_SPHERE:
		return Manager->addSphereSceneNode(5, 16, parent);
	case ESNT_TEXT:
		return Manager->addTextSceneNode(0, L"example");
	case ESNT_WATER_SURFACE:
		return Manager->addWaterSurfaceSceneNode(0, 2.0f, 300.0f, 10.0f, parent);
	case ESNT_TERRAIN:
		return Manager->addTerrainSceneNode("", parent, -1,
							core::vector3df(0.0f,0.0f,0.0f),
							core::vector3df(0.0f,0.0f,0.0f),
							core::vector3df(1.0f,1.0f,1.0f),
							video::SColor(255,255,255,255),
							4, ETPS_17, 0, true);
	case ESNT_SKY_BOX:
		return Manager->addSkyBoxSceneNode(0,0,0,0,0,0, parent);
	case ESNT_SKY_DOME:
		return Manager->addSkyDomeSceneNode(0, 16, 8, 0.9f, 2.0f, 1000.0f, parent);
	case ESNT_SHADOW_VOLUME:
		return 0;
	case ESNT_OCTREE:
		return Manager->addOctreeSceneNode((IMesh*)0, parent, -1, 128, true);
	case ESNT_MESH:
		return Manager->addMeshSceneNode(0, parent, -1, core::vector3df(),
										 core::vector3df(), core::vector3df(1,1,1), true);
	case ESNT_LIGHT:
		return Manager->addLightSceneNode(parent);
	case ESNT_EMPTY:
		return Manager->addEmptySceneNode(parent);
	case ESNT_DUMMY_TRANSFORMATION:
		return Manager->addDummyTransformationSceneNode(parent);
	case ESNT_CAMERA:
		return Manager->addCameraSceneNode(parent);
	case ESNT_CAMERA_MAYA:
		return Manager->addCameraSceneNodeMaya(parent);
	case ESNT_CAMERA_FPS:
		return Manager->addCameraSceneNodeFPS(parent);
	case ESNT_BILLBOARD:
		return Manager->addBillboardSceneNode(parent);
	case ESNT_ANIMATED_MESH:
		return Manager->addAnimatedMeshSceneNode(0, parent, -1, core::vector3df(),
												 core::vector3df(), core::vector3df(1,1,1), true);
	case ESNT_PARTICLE_SYSTEM:
		return Manager->addParticleSystemSceneNode(true, parent);
	default:
		break;
	}

	return 0;
}
