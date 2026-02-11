beginScene(bool backBuffer, bool zBuffer, SColor color,
		const SExposedVideoData& videoData, core::rect<s32>* sourceRect)
{
	CNullDriver::beginScene(backBuffer, zBuffer, color, videoData, sourceRect);
	WindowId=videoData.D3D9.HWnd;
	SceneSourceRect = sourceRect;

	if (backBuffer && BackBuffer)
		BackBuffer->fill(color);

	if (ZBuffer && zBuffer)
		ZBuffer->clear();

	return true;
}
