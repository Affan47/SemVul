saveScene(void)
{
	IrrlichtDevice *device = createDevice( EDT_NULL, dimension2d<u32>(160, 120), 32);
	assert_log(device);
	if (!device)
		return false;

	ISceneManager * smgr = device->getSceneManager();

	ISkinnedMesh* mesh = (ISkinnedMesh*)smgr->getMesh("../media/ninja.b3d");
	if (!mesh)
		return false;

	IAnimatedMeshSceneNode* node1 = smgr->addAnimatedMeshSceneNode(mesh);
	if (node1)
	{
		node1->setPosition(vector3df(-3, -3, 10));
		node1->setMaterialFlag(EMF_LIGHTING, false);
		node1->setAnimationSpeed(0.f);
		node1->setCurrentFrame(10.f);
		node1->setDebugDataVisible(irr::scene::EDS_BBOX_BUFFERS);
	}

	ISkinnedMesh* mesh2 = (ISkinnedMesh*)smgr->getMesh(device->getFileSystem()->getAbsolutePath("../media/dwarf.x"));
	if (!mesh2)
		return false;

	IAnimatedMeshSceneNode* node2 = smgr->addAnimatedMeshSceneNode(mesh2);
	if (node2)
	{
		node2->setPosition(vector3df(33, -93, 120));
		node2->setMaterialFlag(EMF_LIGHTING, false);
		node2->setAnimationSpeed(10.f);
		node2->setCurrentFrame(2.f);
	}

	IAnimatedMeshSceneNode* node3 = smgr->addAnimatedMeshSceneNode(mesh2, node2);
	if (node3)
	{
		node3->setPosition(vector3df(-88, -300, 150));
		node3->setMaterialFlag(EMF_LIGHTING, false);
		node3->setAnimationSpeed(0.f);
		node3->setCurrentFrame(12.f);
	}

	smgr->addCameraSceneNode();

	logTestString("Test scene.irr");
	smgr->saveScene("results/scene.irr");
	bool result = xmlCompareFiles(device->getFileSystem(), "results/scene.irr", "media/scene.irr");

	logTestString("Test scene2.irr");
	smgr->saveScene("results/scene2.irr", 0, node3);
	result &= xmlCompareFiles(device->getFileSystem(), "results/scene2.irr", "media/scene2.irr");

	device->closeDevice();
	device->run();
	device->drop();

	return result;
}
