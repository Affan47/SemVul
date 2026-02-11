post()
{
    again:
    if( 0 != sem_post(&_handle) )
    {
        if(errno == EINTR)
            goto again;

        throw SystemError("sem_post");
    }
}

}
