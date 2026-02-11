testExactPlacement(video::E_DRIVER_TYPE driverType)
{


	IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(160,120), 32);

	if (device == 0)
		return true;

	video::IVideoDriver* driver = device->getVideoDriver();

	if (driver->getColorFormat() != video::ECF_A8R8G8B8 || !driver->queryFeature(video::EVDF_RENDER_TO_TARGET))
	{
		device->closeDevice();
		device->run();
		device->drop();
		return true;
	}

	stabilizeScreenBackground(driver);

	logTestString("Testing driver %ls\n", driver->getName());

	video::ITexture* rt=driver->addRenderTargetTexture(core::dimension2d<u32>(32,32), "rt1");
	video::ITexture *tex=driver->getTexture("../media/fireball.bmp");

	driver->beginScene(true, true, video::SColor(255,40,40,255));
	driver->setRenderTarget(rt);
	driver->draw2DImage(tex, core::recti(0,0,32,32), core::recti(0,0,64,64));
	driver->setRenderTarget(0);
	driver->endScene();

	video::IImage* img = driver->createImage(rt, core::vector2di(), rt->getSize());
	driver->writeImageToFile(img, "results/fireball.png");
	img->drop();
	bool result = fuzzyCompareImages(driver, "media/fireball.png", "results/fireball.png")>98.25f;

	device->closeDevice();
	device->run();
	device->drop();

	return result;
}
