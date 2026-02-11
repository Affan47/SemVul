onInput(IOStream& ios)
{
    while (ios.buffer().in_avail() > 0)
    {
        if (advance(ios.buffer().sbumpc()))
        {
            if (_failed)
            {
                replyError(ios, _errorMessage.c_str(), 0);
            }
            else
            {
                try
                {
                    _result = _proc->endCall();
                    reply(ios);
                }
                catch (const RemoteException& e)
                {
                    ios.buffer().discard();
                    replyError(ios, e.what(), e.rc());
                }
                catch (const std::exception& e)
                {
                    ios.buffer().discard();
                    replyError(ios, e.what(), 0);
                }
            }

            _serviceRegistry.releaseProcedure(_proc);
            _proc = 0;
            _args = 0;
            _result = 0;
            _state = state_0;
            _failed = false;
            _errorMessage.clear();

            return true;
        }
    }

    return false;
}
