callback( void *_caller ) {


    if (!((PS_Node *)_caller)->hasProbes()) return;


    IDSet      path;
    PS_NodePtr current_node = db_path;
    while (current_node->hasChildren()) {

        pair<bool,PS_NodePtr> child = current_node->getChild( 0 );
        ps_assert(child.first);
        current_node = child.second;

        SpeciesID id = current_node->getNum();

        ID2IDMapCIter db_id = db_file2db_id_map.find( id );
        path.insert( (db_id == db_file2db_id_map.end()) ? id : db_id->second );
    }


    current_node = db_rootnode;
    for (IDSetCIter id=path.begin(); id != path.end(); ++id) {
        current_node = current_node->assertChild( *id );
    }


    current_node->addProbes( ((PS_Node *)_caller)->getProbesBegin(), ((PS_Node *)_caller)->getProbesEnd() );
}
