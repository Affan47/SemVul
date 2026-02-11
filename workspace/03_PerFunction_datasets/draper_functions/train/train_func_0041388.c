PS_make_map_for_candidate( PS_CandidatePtr _candidate ) {


    if (_candidate->map) return;
    _candidate->map = new PS_BitMap_Counted( false, __MAX_ID+1 );
    _candidate->map->copy( __PRESET_MAP );
    PS_apply_path_to_bitmap( _candidate->path, true, _candidate->map );
    PS_CandidatePtr parent = _candidate->parent;
    while ((parent != 0) && (parent->path.size() > 0)) {
        PS_apply_path_to_bitmap( parent->path, true, _candidate->map );
        parent = parent->parent;
    }
}
