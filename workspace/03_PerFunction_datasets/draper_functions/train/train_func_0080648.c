Sync()
    {
	if (m_bDirty && !dga)
	{
	    Lock();
	    m_bDirty = false;


	    SDL_UpdateRect(screen, cliprect.x, cliprect.x,
			   cliprect.w, cliprect.h);
	    Unlock();
	}


	emutex.Lock();
	econd.Broadcast();
	emutex.Unlock();
	return 0;
    }
