slurm_auth_marshal_args( void *hosts, int timeout )
{
        static int hostlist_idx = -1;
        static int timeout_idx = -1;
        static int count = sizeof( auth_args ) / sizeof( struct _arg_desc ) - 1;
        void **argv;


        if ( ( hostlist_idx == -1 ) &&
             ( timeout_idx == -1 ) ) {
                hostlist_idx = arg_idx_by_name( auth_args, ARG_HOST_LIST );
                timeout_idx = arg_idx_by_name( auth_args, ARG_TIMEOUT );
        }

        argv = xmalloc( count * sizeof( void * ) );


        argv[ hostlist_idx ] = hosts;


        argv[ timeout_idx ] = ((char *) NULL) + timeout;

        return argv;
}
