enqueueOperation( const LogDataOperation* newOperation )
{
    if ( currentOperation_ == NULL )
    {

        currentOperation_ = newOperation;
        startOperation();
    }
    else
    {


        if ( nextOperation_ != NULL )
            delete nextOperation_;
        nextOperation_ = newOperation;
    }
}
