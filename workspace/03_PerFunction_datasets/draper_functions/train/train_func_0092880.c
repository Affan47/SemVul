filter_init( policy_flags_t policy, enum filter_action act,
                int init_group )
{
        struct filter *filt;

        filt = mem_alloc( sizeof( *filt));
        memset( filt, 0, sizeof( *filt ));
        filt->action = act;
        filt->policy = policy;
        if ( init_group )
                filt->group = group_init();

        return filt;
}
