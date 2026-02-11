check_abone_res( const int number )
{
    if( ! m_vec_abone_res.size() ) return false;
    if( ! m_vec_abone_res[ number ] ) return false;

    NODE* head = res_header( number );
    if( ! head ) return false;
    if( ! head->headinfo ) return false;

    head->headinfo->abone = true;
    return true;
}
