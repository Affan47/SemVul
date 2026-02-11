ParseCameraChunk()
{
	ASSIMP_3DS_BEGIN_CHUNK();
	aiCamera* camera = mScene->mCameras.back();


	switch (chunk.Flag)
	{

	case Discreet3DS::CHUNK_CAM_RANGES:
		camera->mClipPlaneNear = stream->GetF4();
		camera->mClipPlaneFar  = stream->GetF4();
		break;
	}

	ASSIMP_3DS_END_CHUNK();
}
