setDirection(PlayerDirections::Direction direction)
{
	if (m_blockSwitchDir)
	{
		return;
	}
	else if (direction == PlayerDirections::Up && m_dir == PlayerDirections::Down)
	{
		return;
	}
	else if (direction == PlayerDirections::Down && m_dir == PlayerDirections::Up)
	{
		return;
	}
	else if (direction == PlayerDirections::Left && m_dir == PlayerDirections::Right)
	{
		return;
	}
	else if (direction == PlayerDirections::Right && m_dir == PlayerDirections::Left)
	{
		return;
	}

	m_dir = direction;
	m_blockSwitchDir = true;
}
