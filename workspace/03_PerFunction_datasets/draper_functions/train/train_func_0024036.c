finalize()
{
    IceUtil::StaticMutex::Lock lock(_m);
    if(--_initCount == 0)
    {
	delete factoryTable;
    }
}
