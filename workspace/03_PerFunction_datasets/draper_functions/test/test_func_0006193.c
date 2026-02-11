shredule( Chuck_VM_Shred * shred,
                                       t_CKTIME wake_time )
{

    if( shred->prev || shred->next )
    {


        EM_error3( "[chuck](VM): internal sanity check failed in shredule()" );
        EM_error3( "[chuck](VM): (shred shreduled while shreduled)" );

        return FALSE;
    }


    if( wake_time < (this->now_system - .5) )
    {

        EM_error3( "[chuck](VM): internal sanity check failed in shredule()" );
        EM_error3( "[chuck](VM): (wake time is past) - %f : %f", wake_time, this->now_system );

        return FALSE;
    }

    shred->wake_time = wake_time;


    if( !shred_list )
        shred_list = shred;
    else
    {

        Chuck_VM_Shred * curr = shred_list;
        Chuck_VM_Shred * prev = NULL;

        while( curr )
        {

            if( curr->wake_time > wake_time )
                break;

            prev = curr;
            curr = curr->next;
        }

        if( !prev )
        {
            shred->next = shred_list;
            if( shred_list ) shred_list->prev = shred;
            shred_list = shred;
        }
        else
        {

            shred->next = prev->next;
            shred->prev = prev;
            if( prev->next ) prev->next->prev = shred;
            prev->next = shred;
        }
    }

    return TRUE;
}
