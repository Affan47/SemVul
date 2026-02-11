removeAll()
{
	ISceneNode::removeAll();
	setActiveCamera(0);

	if (Driver)
		Driver->setMaterial(video::SMaterial());
}
