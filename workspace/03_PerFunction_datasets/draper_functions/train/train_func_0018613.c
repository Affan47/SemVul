generate()
{
	const double sqrt3 = 1.7320508075688772935274463415059;

	std::cout << "Generating" << std::endl;

	size_t steps = 0;
	while( actives.size() > 0 )
	{
		SSMFVertex *vtx = static_cast<SSMFVertex *>( actives.first() );

		if( !vtx->borderTest( ) )
		{
			double nx, ny;
			if( vtx->computeNewCoordinates( *bg, nx, ny ) > 0)
			{
				MeshNode *nd = new MeshNode( nx, ny );

				if( addSite( vtx, nd, false, false ) == true )
				{
					if( deleted.size() == 1 )
					{

						vtx->unDelete();
						vtx->makeAccepted();
						vtx->radiate( actives );
						deleted.erase( deleted.begin(), deleted.end() );
					}
					else
					{
						actives.removeRelevants( deleted );

						int len = newVertices.size(), i;
						for( i = 0; i < len; ++i )
						{
							SSMFVertex *vs = static_cast<SSMFVertex *>( newVertices[i] );
							vs->setBody( tag );
						}

						for( i = 0; i < len; ++i )
						{
							SSMFVertex *vs = static_cast<SSMFVertex *>( newVertices[i] );
							double ref = bg->interpolate( vs->vx, vs->vy ) / sqrt3;
							if( vs->rightSize( ref ) )
							{
								vs->makeAccepted();
							}
							else
							{
								if( !vs->testIfActive( actives ) )
								{
									vs->makeWaiting();
								}
							}
						}

						for( i = 0; i < len; ++i )
						{
							SSMFVertex *vs = static_cast<SSMFVertex *>( newVertices[i] );
							if( vs->isWaiting() )
							{
								vs->testIfActive( actives );
							}
							else if( vs->isAccepted() )
							{
								vs->radiate( actives );
							}
						}
					}
				}

				recycle();
			}
		}
		++steps;
	}
}
