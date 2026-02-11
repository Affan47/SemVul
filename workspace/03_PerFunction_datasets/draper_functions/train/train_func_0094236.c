ballMoved()
{
	if (putter->isVisible())
	{
		putter->setPos((*curPlayer).ball()->x(), (*curPlayer).ball()->y());
		updateMouse();
	}
}
