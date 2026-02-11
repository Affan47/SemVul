create ( const std::string& name ) {
    node_debug ( "Create Register: " << name );
    return NodeRef ( new Register ( name ) );
}
