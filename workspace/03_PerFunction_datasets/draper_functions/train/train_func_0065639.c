addResponseHandler(uint16 channel, ResponseHandler* rh)
    {
        ResponseHandlerListByChannel::iterator i = mResponseHandlers.find(channel);
        if (i == mResponseHandlers.end())
            i = mResponseHandlers.insert(ResponseHandlerListByChannel::value_type(channel, ResponseHandlerList())).first;

        ResponseHandlerList& handlers = i->second;
        if (std::find(handlers.begin(), handlers.end(), rh) == handlers.end())
            handlers.push_back(rh);
    }
