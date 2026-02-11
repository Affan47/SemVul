startNewRound( bool incrementRound, const QString & layout )
{
	cleanUpRound();

	m_waitingOutRound = false;

	m_coordinator->beginNewAnimationStage();

	if ( incrementRound )
	{
		++m_round;

		if ( m_rules->energyEnabled() )
		{
			m_maxEnergy += m_rules->maxEnergyAddedEachRound();
			updateEnergy( m_rules->energyAddedEachRound() );
		}
		m_robotCount += m_rules->enemiesAddedEachRound();
		m_fastbotCount += m_rules->fastEnemiesAddedEachRound();
		m_junkheapCount += m_rules->junkheapsAddedEachRound();
	}

	if ( layout.isEmpty() )
	{

		const QPoint centre = QPoint( qRound( m_rules->columns() / 2 ), qRound( m_rules->rows() / 2 ) );
		m_hero = m_coordinator->createSprite( Hero, centre );


		for ( int i = m_junkheapCount; i > 0 ; --i )
		{
			const QPoint point = randomEmptyCell();
			m_junkheaps << m_coordinator->createSprite( Junkheap, point );
			m_spriteMap.insert( point, m_junkheaps.last() );
		}


		for ( int i = m_robotCount; i > 0; --i )
		{
			const QPoint point = randomEmptyCell();
			m_bots << m_coordinator->createSprite( Robot, point );
			m_spriteMap.insert( point, m_bots.last() );
		}


		for ( int i = m_fastbotCount; i > 0; --i )
		{
			const QPoint point = randomEmptyCell();
			m_bots << m_coordinator->createSprite( Fastbot, point );
			m_spriteMap.insert( point, m_bots.last() );
		}
	}
	else
	{
		const QStringList rows = layout.split('\n');
		for ( int r = 0; r < rows.size(); ++r )
		{
			for ( int c = 0; c < rows.at( r ).size(); ++c )
			{
				const QChar ch = rows.at( r ).at( c );
				const QPoint point( c, r );

				if ( ch == 'h' && m_hero == 0 )
					m_hero = m_coordinator->createSprite( Hero, point );
				else if ( ch == 'r' )
					m_bots << m_coordinator->createSprite( Robot, point );
				else if ( ch == 'f' )
					m_bots << m_coordinator->createSprite( Fastbot, point );
				else if ( ch == 'j' )
					m_junkheaps << m_coordinator->createSprite( Junkheap, point );
			}
		}
	}

	emit roundChanged( m_round );
	emit scoreChanged( m_score );
	emit enemyCountChanged( m_bots.size() );
	emit energyChanged( m_energy );

	refreshSpriteMap();
}
