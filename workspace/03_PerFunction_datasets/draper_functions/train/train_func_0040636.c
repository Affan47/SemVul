check_conflict( const int mode, const std::string& str_motion )
{
    std::vector< int > vec_ids;

    std::vector< MouseKeyItem >::iterator it = m_vec_items.begin();
    for( ; it != m_vec_items.end(); ++it ){

        const int id = (*it).is_activated( mode, str_motion );
        if( id != CONTROL::None ) vec_ids.push_back( id );
    }

    return vec_ids;
}
