httpErrorNofinishStreamHandler(int status,
                               FdEventHandlerPtr event,
                               StreamRequestPtr srequest)
{
    if(status == 0 && !streamRequestDone(srequest))
        return 0;

    return 1;
}
