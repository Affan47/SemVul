guiDisabledMenu(void)
{
	IrrlichtDevice *device = createDevice( video::EDT_BURNINGSVIDEO,
											dimension2d<u32>(160, 40), 32);
	assert_log(device);
	if (!device)
		return false;

	video::IVideoDriver* driver = device->getVideoDriver();
	gui::IGUIEnvironment* env = device->getGUIEnvironment();

	gui::IGUIContextMenu* menu = env->addMenu();
	menu->addItem(L"Menu", -1, true, true);
	gui::IGUIContextMenu* subMenu = menu->getSubMenu(0);
	subMenu->addItem(L"Submenu 1", -1, false, true);
	gui::IGUIContextMenu* subSubMenu = subMenu->getSubMenu(0);
	subSubMenu->addItem(L"Final item");

	SEvent event;
	event.EventType = EET_MOUSE_INPUT_EVENT;
	event.MouseInput.Event = EMIE_LMOUSE_PRESSED_DOWN;
	event.MouseInput.X = menu->getAbsolutePosition().UpperLeftCorner.X + 1;
	event.MouseInput.Y = menu->getAbsolutePosition().UpperLeftCorner.Y + 1;
	(void)menu->OnEvent(event);


	event.MouseInput.Event = EMIE_MOUSE_MOVED;
	event.MouseInput.X = subMenu->getAbsolutePosition().UpperLeftCorner.X + 40;
	event.MouseInput.Y = subMenu->getAbsolutePosition().UpperLeftCorner.Y + 10;
	(void)menu->OnEvent(event);

	device->run();
	driver->beginScene(true, true, video::SColor(150,50,50,50));
	env->drawAll();
	driver->endScene();

	bool result = takeScreenshotAndCompareAgainstReference(driver, "-guiDisabledMenu.png", 98.77f);
	device->closeDevice();
	device->run();
	device->drop();

	return result;
}
