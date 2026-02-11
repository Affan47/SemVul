wasp_task_cb( int fd, short evt, void* context ){
    wasp_task task = (wasp_task) context;

    if( ! task->pending ) return;
    int ms = task->task_mt( task );

    if( ms ){
        task->time.tv_sec = ms / 1000;
        task->time.tv_usec = ((ms % 1000)) * 1000;
        evtimer_add( &( task->event ), &( task->time ) );
    }else{
        task->pending = 0;
        wasp_disable_os_loop( );
        wasp_unroot_obj( (wasp_object) task );
    };
}
