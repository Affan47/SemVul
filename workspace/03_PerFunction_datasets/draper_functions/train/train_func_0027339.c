puttPress()
{


	if (!putting && !stroking && !inPlay)
	{
		puttCount = 0;
		puttReverse = false;
		putting = true;
		stroking = false;
		strength = 0;
		if (m_useAdvancedPutting)
		{
			strokeCircle->setValue(0);
			int pw = (int)(putter->line().x2() - putter->line().x1());
			if (pw < 0) pw = -pw;
			int px = (int)putter->x() + pw / 2;
			int py = (int)putter->y();
			if (px > width / 2 && py < height / 2)
				strokeCircle->setPos(px/2 - pw / 2 - 5 - strokeCircle->width()/2, py/2 + 5);
			else if (px > width / 2)
				strokeCircle->setPos(px/2 - pw / 2 - 5 - strokeCircle->width()/2, py/2 - 5 - strokeCircle->height()/2);
			else if (py < height / 2)
				strokeCircle->setPos(px/2 + pw / 2 + 5, py/2 + 5);
			else
				strokeCircle->setPos(px/2 + pw / 2 + 5, py/2 - 5 - strokeCircle->height()/2);
			strokeCircle->setVisible(true);
		}
		putterTimer->start(putterTimerMsec);
	}
	else if (m_useAdvancedPutting && putting && !editing)
	{
		putting = false;
		stroking = true;
		puttReverse = false;
		finishStroking = false;
	}
	else if (m_useAdvancedPutting && stroking)
	{
		finishStroking = true;
		putterTimeout();
	}
}
