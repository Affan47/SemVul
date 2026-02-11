detach()
{
    _detached = true;

    if( _id )
    {
        int ret = pthread_detach(_id);
        if(ret != 0)
            throw SystemError("pthread_detach");
    }
}
