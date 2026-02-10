tick()
{
	checkCollisions();

	foreach( KBounceBall* ball, m_balls )
	{
	    ball->goForward();
	}
	foreach( KBounceWall* wall, m_walls )
	{
	    wall->goForward();
	}

	foreach( KBounceBall* ball, m_balls )
	{
	    ball->update();
	}

	foreach( KBounceWall* wall, m_walls )
	{
	    wall->update();
	}
}
