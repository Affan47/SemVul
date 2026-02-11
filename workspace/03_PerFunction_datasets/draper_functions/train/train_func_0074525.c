camAllocateKeypoints(CamKeypoints *fpoints, int nbPoints)
{
    CAM_CHECK_ARGS(camAllocateKeypoints, fpoints != NULL);
    fpoints->nbPoints = 0;
    if (nbPoints) {
	fpoints->keypoint = (CamKeypoint**)malloc(sizeof(CamKeypoint*) * nbPoints);
	if (fpoints->keypoint == NULL) {
	    fpoints->allocated = 0;
	    camError("camAllocateKeypoints", "Memory allocation error");
	    return 0;
	}
    } else fpoints->keypoint = NULL;
    fpoints->bag = NULL;
    fpoints->allocated = nbPoints;
    return 1;
}
