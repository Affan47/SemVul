PS_find_probes( const PS_NodePtr _root_node, const int _round, PS_CandidatePtr _candidate_parent, const float _filling_level ) {


    __PROBES_COUNTER             = 0;
    __CANDIDATES_COUNTER         = 0;
    __SOURCE_MIN_MATCH_COUNT     = (__SOURCE_ID_SET.size() * (__MIN_PERCENTAGE_SET_MATCH - (_round * 5))) / 100.0;
    __SOURCE_MAX_MATCH_COUNT     = (__SOURCE_ID_SET.size() * (__MAX_PERCENTAGE_SET_MATCH + (_round * 5))) / 100.0;
    __TARGET_MIN_MATCH_COUNT     = (__TARGET_ID_SET.size() * (__MIN_PERCENTAGE_SET_MATCH - (_round * 5))) / 100.0;
    __TARGET_MAX_MATCH_COUNT     = (__TARGET_ID_SET.size() * (__MAX_PERCENTAGE_SET_MATCH + (_round * 5))) / 100.0;
    __SOURCE_PERFECT_MATCH_COUNT = __SOURCE_ID_SET.size() / 2.0;
    __TARGET_PERFECT_MATCH_COUNT = __TARGET_ID_SET.size() / 2.0;
    __MIN_SETS_ID = (*__SOURCE_ID_SET.begin()  < *__TARGET_ID_SET.begin())  ? *__SOURCE_ID_SET.begin()  : *__TARGET_ID_SET.begin();
    __MAX_SETS_ID = (*__SOURCE_ID_SET.rbegin() < *__TARGET_ID_SET.rbegin()) ? *__SOURCE_ID_SET.rbegin() : *__TARGET_ID_SET.rbegin();
    printf( "PS_find_probes(%i) : source match %10.3f .. %10.3f   target match %10.3f .. %10.3f\n", _round, __SOURCE_MIN_MATCH_COUNT, __SOURCE_MAX_MATCH_COUNT, __TARGET_MIN_MATCH_COUNT, __TARGET_MAX_MATCH_COUNT ); fflush( stdout );

    struct tms before;
    times( &before );
    for ( PS_NodeMapConstIterator i = _root_node->getChildrenBegin();
          (i != _root_node->getChildrenEnd()) && (i->first < __MAX_SETS_ID);
          ++i ) {

        __PATH.clear();
        PS_find_probe_for_sets( i->second, _candidate_parent );
    }
    printf( "PS_find_probes(%i) : %li candidates of %li probes visited  ", _round, __CANDIDATES_COUNTER, __PROBES_COUNTER );
    PS_print_time_diff( &before );

    _candidate_parent->reduceChildren( _filling_level );
    for ( PS_CandidateByGainMapCIter c = _candidate_parent->children.begin();
          c != _candidate_parent->children.end();
          ++c ) {
        printf( "PS_find_probes(%i) : ", _round );
        c->second->print();
        ++__CANDIDATES_TODO;
    }
    fflush( stdout );
}
