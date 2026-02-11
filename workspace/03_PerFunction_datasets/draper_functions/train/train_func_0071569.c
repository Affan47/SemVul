getRayFromScreenCoordinates(
	const core::position2d<s32> & pos, ICameraSceneNode* camera)
{
	core::line3d<f32> ln(0,0,0,0,0,0);

	if (!SceneManager)
		return ln;

	if (!camera)
		camera = SceneManager->getActiveCamera();

	if (!camera)
		return ln;

	const scene::SViewFrustum* f = camera->getViewFrustum();

	core::vector3df farLeftUp = f->getFarLeftUp();
	core::vector3df lefttoright = f->getFarRightUp() - farLeftUp;
	core::vector3df uptodown = f->getFarLeftDown() - farLeftUp;

	const core::rect<s32>& viewPort = Driver->getViewPort();
	core::dimension2d<u32> screenSize(viewPort.getWidth(), viewPort.getHeight());

	f32 dx = pos.X / (f32)screenSize.Width;
	f32 dy = pos.Y / (f32)screenSize.Height;

	if (camera->isOrthogonal())
		ln.start = f->cameraPosition + (lefttoright * (dx-0.5f)) + (uptodown * (dy-0.5f));
	else
		ln.start = f->cameraPosition;

	ln.end = farLeftUp + (lefttoright * dx) + (uptodown * dy);

	return ln;
}
