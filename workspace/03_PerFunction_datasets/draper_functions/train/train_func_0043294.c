main()
{

	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;


	IrrlichtDevice *device = createDevice(driverType,
			core::dimension2d<u32>(640, 480), 16, false);

	if (device == 0)
		return 1;


	device->setWindowCaption(L"Custom Scene Node - Irrlicht Engine Demo");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	smgr->addCameraSceneNode(0, core::vector3df(0,-40,0), core::vector3df(0,0,0));


	CSampleSceneNode *myNode =
		new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);


	scene::ISceneNodeAnimator* anim =
		smgr->createRotationAnimator(core::vector3df(0.8f, 0, 0.8f));

	if(anim)
	{
		myNode->addAnimator(anim);


		anim->drop();
		anim = 0;
	}


	myNode->drop();
	myNode = 0;


	u32 frames=0;
	while(device->run())
	{
		driver->beginScene(true, true, video::SColor(0,100,100,100));

		smgr->drawAll();

		driver->endScene();
		if (++frames==100)
		{
			core::stringw str = L"Irrlicht Engine [";
			str += driver->getName();
			str += L"] FPS: ";
			str += (s32)driver->getFPS();

			device->setWindowCaption(str.c_str());
			frames=0;
		}
	}

	device->drop();

	return 0;
}
