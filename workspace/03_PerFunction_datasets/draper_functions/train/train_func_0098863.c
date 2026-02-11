write_marker_address(uchar *p, int size,
    int zmachine_area, int32 offset, int32 value)
{


    int32 addr = 0;

    switch(zmachine_area)
    {
        case DYNAMIC_ARRAY_ZA:
            addr = m_vars_offset; break;
        case ZCODE_ZA:
            addr = m_code_offset; break;
        case STATIC_STRINGS_ZA:
            addr = m_strs_offset; break;
        case DICTIONARY_ZA:
            addr = m_dict_offset; break;
        case OBJECT_TREE_ZA:
            addr = m_objs_offset; break;
        case PROP_ZA:
            addr = m_props_offset; break;
        case INDIVIDUAL_PROP_ZA:
            addr = m_individuals_offset; break;
    }
    if (size == 1) { p[addr+offset] = value%256; return; }
    p[addr+offset] = value/256;
    p[addr+offset+1] = value%256;
}
