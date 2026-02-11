collisionDetect()
{
	if (!isVisible() || state == Holed || !m_doDetect)
		return;


	m_collisionId = (m_collisionId + 1) % 2;
	if (m_collisionId == 1 && !velocity().isNull())
		friction();

	const double initialVelocity = Vector(velocity()).magnitude();
	const double minSpeed = .06;

	QList<QGraphicsItem *> items = collidingItems();

	bool doTerrainCollisions = true;
	foreach (QGraphicsItem* item, items)
	{
		if (item->data(0) == Rtti_NoCollision || item->data(0) == Rtti_Putter)
			continue;

		if (!isVisible() || state == Holed)
			return;

		CanvasItem *citem = dynamic_cast<CanvasItem *>(item);
		if (citem)
		{
			if (!citem->terrainCollisions())
			{

				const bool allowTerrainCollisions = citem->collision(this);
				doTerrainCollisions = doTerrainCollisions && allowTerrainCollisions;
			}
			break;
		}
	}

	if (doTerrainCollisions)
	{
		foreach (QGraphicsItem* item, items)
		{
			CanvasItem *citem = dynamic_cast<CanvasItem *>(item);
			if (citem && citem->terrainCollisions())
			{


				if (!citem->collision(this))
				{
					break;
				}
			}
		}
	}

	const double currentVelocity = Vector(velocity()).magnitude();
	const double velocityChange = qAbs(initialVelocity - currentVelocity);

	if(currentVelocity < minSpeed && velocityChange < minSpeed && currentVelocity)
	{

		setVelocity(Vector());
		setState(Stopped);
	}
}
