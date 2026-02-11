testGetSceneNodeFromScreenCoordinatesBB(IrrlichtDevice * device,
						ISceneManager * smgr,
						ISceneCollisionManager * collMgr)
{

	IMeshSceneNode * cubeNode1 = smgr->addCubeSceneNode(10.f, 0, -1, vector3df(0, 0, 4));
	IMeshSceneNode * cubeNode2 = smgr->addCubeSceneNode(10.f, 0, -1, vector3df(0, 0, 30));
	cubeNode2->setRotation(vector3df(90.f, 90.f, 90.f));
	IMeshSceneNode * cubeNode3 = smgr->addCubeSceneNode(10.f, 0, -1, vector3df(0, 0, 40));
	cubeNode3->setRotation(vector3df(180.f, 180.f, 180.f));

	ICameraSceneNode * camera = smgr->addCameraSceneNode();
	device->run();
	smgr->drawAll();

	ISceneNode * hitNode = collMgr->getSceneNodeFromScreenCoordinatesBB(position2d<s32>(80, 60));


	bool result = true;
	if(hitNode != cubeNode1)
	{
		logTestString("Unexpected node hit. Expected cubeNode1.\n");
		result = false;
	}


	cubeNode1->setVisible(false);
	hitNode = collMgr->getSceneNodeFromScreenCoordinatesBB(position2d<s32>(80, 60));
	if(hitNode != cubeNode2)
	{
		logTestString("Unexpected node hit. Expected cubeNode2.\n");
		result = false;
	}


	cubeNode2->setParent(cubeNode1);


	bool visible = cubeNode2->isVisible();
	if(!visible)
	{
		logTestString("cubeNode2 should think that it (in isolation) is visible.\n");
		result = false;
	}

	visible = cubeNode2->isTrulyVisible();
	if(visible)
	{
		logTestString("cubeNode2 should know that it (recursively) is invisible.\n");
		result = false;
	}


	hitNode = collMgr->getSceneNodeFromScreenCoordinatesBB(position2d<s32>(80, 60));
	if(hitNode != cubeNode3)
	{
		logTestString("Unexpected node hit. Expected cubeNode3.\n");
		result = false;
	}


	cubeNode1->setVisible(true);
	cubeNode1->setID(0xAAAAAAAA);
	hitNode = collMgr->getSceneNodeFromScreenCoordinatesBB(position2d<s32>(80, 60), 0x55555555);
	if(hitNode != cubeNode2)
	{
		logTestString("Unexpected node hit. Expected cubeNode2.\n");
		result = false;
	}
	assert_log(result);

	smgr->clear();

	return result;
}
