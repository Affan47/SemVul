run()
{
	core::dimension2d<u32> resolution (800, 600);

	if ( driverType == video::EDT_BURNINGSVIDEO || driverType == video::EDT_SOFTWARE )
	{
		resolution.Width = 640;
		resolution.Height = 480;
	}

	irr::SIrrlichtCreationParameters params;
	params.DriverType=driverType;
	params.WindowSize=resolution;
	params.Bits=32;
	params.Fullscreen=fullscreen;
	params.Stencilbuffer=shadows;
	params.Vsync=vsync;
	params.AntiAlias=aa?8:0;
	params.EventReceiver=this;

	device = createDeviceEx(params);
	if (!device)
		return;

	if (device->getFileSystem()->existFile("irrlicht.dat"))
		device->getFileSystem()->addFileArchive("irrlicht.dat");
	else
		device->getFileSystem()->addFileArchive("../../media/irrlicht.dat");
	if (device->getFileSystem()->existFile("map-20kdm2.pk3"))
		device->getFileSystem()->addFileArchive("map-20kdm2.pk3");
	else
		device->getFileSystem()->addFileArchive("../../media/map-20kdm2.pk3");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	device->setWindowCaption(L"Irrlicht Engine Demo");


	smgr->setAmbientLight ( video::SColorf ( 0x00c0c0c0 ) );

	wchar_t tmp[255];


	s32 now = 0;
	s32 lastfps = 0;
	sceneStartTime = device->getTimer()->getTime();
	while(device->run() && driver)
	{
		if (device->isWindowActive())
		{
			#ifdef USE_IRRKLANG

			scene::ICameraSceneNode* cam = smgr->getActiveCamera();
			if (cam && irrKlang)
				irrKlang->setListenerPosition(cam->getAbsolutePosition(), cam->getTarget());
			#endif


			now = device->getTimer()->getTime();
			if (now - sceneStartTime > timeForThisScene && timeForThisScene!=-1)
				switchToNextScene();

			createParticleImpacts();

			driver->beginScene(timeForThisScene != -1, true, backColor);

			smgr->drawAll();
			guienv->drawAll();
			driver->endScene();


			const s32 nowfps = driver->getFPS();

			swprintf(tmp, 255, L"%ls fps:%3d triangles:%0.3f mio/s",
						driver->getName(), driver->getFPS(),
						driver->getPrimitiveCountDrawn(1) * (1.f / 1000000.f));

			statusText->setText(tmp);
			if ( nowfps != lastfps )
			{
				device->setWindowCaption(tmp);
				lastfps = nowfps;
			}
		}
	}

	device->drop();
}
