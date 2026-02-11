solve(POSITION *parent)
{
	int i, nmoves, qq;
	MOVE *mp, *mp0;
	POSITION *pos;

        bool q;
        all_moves++;


	if (Status != NoSolutionExists) {
		return false;
	}

        {
            QMutexLocker lock( &endMutex );
            if ( m_shouldEnd )
            {
                Status = SearchAborted;
                return false;
            }
        }

        if ( max_positions != -1 && Total_positions > ( unsigned long )max_positions )
        {
            Status = MemoryLimitReached;
            return false;
        }


	if ((mp0 = get_moves(&nmoves)) == NULL) {
            if ( isWon() ) {
                Status = SolutionExists;
                win( parent );
            }
            return false;
	}

        if ( parent->depth == 0 )
        {
            Q_ASSERT( firstMoves.count() == 0 );
            for (int j = 0; j < nmoves; ++j)
                firstMoves.append( Possible[j] );
        }

	parent->nchild = nmoves;


	q = false;
	for (i = 0, mp = mp0; i < nmoves; ++i, ++mp) {
		make_move(mp);


		pilesort();


		if ((pos = new_position(parent, mp)) == NULL) {
			undo_move(mp);
			parent->nchild--;
			continue;
		}


		if (pos->cluster != parent->cluster || !nmoves) {
			qq = solve(pos);
			undo_move(mp);
			if (!qq) {
				free_position(pos, false);
			}
			q |= (bool)qq;
		} else {
			queue_position(pos, mp->pri);
			undo_move(mp);
			q = true;
		}
	}
        MemoryManager::free_array(mp0, nmoves);


	return q;
}
