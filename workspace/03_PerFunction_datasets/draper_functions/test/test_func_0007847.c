find_hmdf_info( Block *bpt, Hmdf_information *hmdf_info_list )
{
    Hmdf_information *ret, *temp;

    temp = NULL;
    if( bpt->kind != BB ){
        for( ret = hmdf_info_list; ret; ret = ret->next ){
            if( ret->block == bpt ){
                if( ret->copy_list != NULL && ret->copy_list->entry == ret ){
                    return( ret );
                }
                temp = ret;
            }
        }
    }else{
        temp = NULL;
    }
    return( temp );
}
