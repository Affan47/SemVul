load( PS_FileBuffer* _fb ) {
    unsigned int size;


    _fb->get_int( num );


    _fb->get_uint( size );
    if (size) {
        probes = new PS_ProbeSet;
        for (unsigned int i=0; i<size; ++i) {
            PS_Probe *p = new PS_Probe;
            _fb->get( p, sizeof(PS_Probe) );
            PS_ProbePtr new_probe(p);
            probes->insert( new_probe );
        }
    } else {
        probes = 0;
    }


    _fb->get_uint( size );
    if (num == -1) {
        for (unsigned int i=0; i<size; ++i) {
            PS_NodePtr new_child(new PS_Node(-1));
            new_child->load( _fb );
            children[new_child->getNum()] = new_child;
            if (i % 200 == 0) printf( "loaded 1st level #%i (%i)\n", i+1, new_child->getNum() );
        }
    } else {
        for (unsigned int i=0; i<size; ++i) {
            PS_NodePtr new_child(new PS_Node(-1));
            new_child->load( _fb );
            children[new_child->getNum()] = new_child;
        }
    }

    return true;
}
