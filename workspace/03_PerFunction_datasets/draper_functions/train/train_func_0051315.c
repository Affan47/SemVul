load_rol_instrument( binistream *f, SBnkHeader const &header, std::string &name )
{
    TInstrumentNames const &ins_name_list = header.ins_name_list;

    int const ins_index = get_ins_index( name );

    if( ins_index != -1 )
    {
        return ins_index;
    }

    typedef TInstrumentNames::const_iterator TInsIter;
    typedef std::pair<TInsIter, TInsIter>    TInsIterPair;

    TInsIterPair range = std::equal_range( ins_name_list.begin(),
                                           ins_name_list.end(),
                                           name,
                                           StringCompare() );

    if( range.first != range.second )
    {
        int const seekOffs = header.abs_offset_of_data + (range.first->index*kSizeofDataRecord);
        f->seek( seekOffs, binio::Set );
    }

    SUsedList usedIns;
    usedIns.name = name;

    if( range.first != range.second )
    {
        read_rol_instrument( f, usedIns.instrument );
    }
    else
    {

        memset( &usedIns.instrument, 0, sizeof(SRolInstrument) );
    }
    ins_list.push_back( usedIns );

    return ins_list.size()-1;
}
