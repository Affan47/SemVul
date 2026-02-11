Validate( const aiCamera* pCamera)
{
	if (pCamera->mClipPlaneFar <= pCamera->mClipPlaneNear)
		ReportError("aiCamera::mClipPlaneFar must be >= aiCamera::mClipPlaneNear");


	if (!pCamera->mHorizontalFOV || pCamera->mHorizontalFOV >= (float)AI_MATH_PI)
		ReportWarning("%f is not a valid value for aiCamera::mHorizontalFOV",pCamera->mHorizontalFOV);
}
