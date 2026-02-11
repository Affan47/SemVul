startBall(const Vector &velocity)
{
	playSound("hit");

	emit inPlayStart();
	putter->setVisible(false);

	(*curPlayer).ball()->setState(Rolling);
	(*curPlayer).ball()->setVelocity(velocity);
	(*curPlayer).ball()->shotStarted();

	foreach (QGraphicsItem* qitem, m_topLevelQItems)
	{
		CanvasItem *citem = dynamic_cast<CanvasItem *>(qitem);
		if (citem)
			citem->shotStarted();
	}

	inPlay = true;
}
