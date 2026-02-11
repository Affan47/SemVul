Timestep( REAL dt )
{
    for ( int i = 0; i < nBandwidthTask::Type_Count; ++i )
    {
        nType type = nType(i);

        nTaskHeap& heap = this->Tasks( type );
        int j;

        static tArray< nBandwidthTask* > tasks;
        tasks.SetLen( 0 );


        for ( j = heap.Len()-1; j>=0; --j )
        {
            tasks[j] = heap(j);
        }

        for ( j = tasks.Len()-1; j>=0; --j )
        {
            tasks(j)->Timestep( dt );
        }
    }

    this->OnChange();
}
