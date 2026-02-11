removeRequestHandler(uint16 channel, RequestHandler* rh)
    {
        OGRE_LOCK_RW_MUTEX_WRITE(mRequestHandlerMutex);

        RequestHandlerListByChannel::iterator i = mRequestHandlers.find(channel);
        if (i != mRequestHandlers.end())
        {
            RequestHandlerList& handlers = i->second;
            for (RequestHandlerList::iterator j = handlers.begin(); j != handlers.end(); ++j)
            {
                if ((*j)->getHandler() == rh)
                {


                    (*j)->disconnectHandler();
                    handlers.erase(j);
                    break;
                }
            }

        }

    }
