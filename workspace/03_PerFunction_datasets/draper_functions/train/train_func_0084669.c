refreshSpriteMap()
{
	m_spriteMap.clear();
	foreach( Sprite * bot, m_bots )
		m_spriteMap.insert( bot->gridPos(), bot );
	foreach( Sprite * junkheap, m_junkheaps )
		m_spriteMap.insert( junkheap->gridPos(), junkheap );
}
