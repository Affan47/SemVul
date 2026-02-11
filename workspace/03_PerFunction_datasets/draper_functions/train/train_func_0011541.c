pixelAccuracy(E_DRIVER_TYPE driverType)
{
	IrrlichtDevice *device = createDevice( driverType, dimension2d<u32>(160, 120), 32);
	if (!device)
		return true;

	IVideoDriver* driver = device->getVideoDriver();

	stabilizeScreenBackground(driver);

	logTestString("Testing driver %ls\n", driver->getName());

	device->getSceneManager()->addCameraSceneNode();

	driver->beginScene(true, true, SColor(255,100,101,140));
	u32 start=0;
	for (u32 count=1; count<10; ++count)
	{
		for (u32 j=0; j<count; ++j)
		{
			for (u32 x=0; x<100-start; ++x)
			{
				driver->drawPixel(start+x, start, (count%2==1)?0xffffffff:0xff000000);
			}
			++start;
		}
	}
	start=0;
	for (u32 count=1; count<10; ++count)
	{
		for (u32 j=0; j<count; ++j)
		{
			for (u32 x=0; x<100-start; ++x)
			{
				driver->drawPixel(start, start+x, (count%2==1)?0xffffffff:0xff000000);
			}
			++start;
		}
	}
	for (u32 x=0; x<100; ++x)
	{
		driver->drawPixel(x, x, 0xffff0000);
	}
	driver->endScene();

	bool result = takeScreenshotAndCompareAgainstReference(driver, "-pixelAccuracy.png");

	device->closeDevice();
	device->run();
	device->drop();

	return result;
}
