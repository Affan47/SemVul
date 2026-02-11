applyForWork ( Thread *th,  Job* previous )
{
    if ( weaver()->activeThreadCount() == 0 )
    {
        weaver()->setState ( Suspended );
    }
    weaver()->waitForAvailableJob ( th );
    return weaver()->applyForWork ( th,  previous );
}
