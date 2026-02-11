innerPartFromNode( DOM::NodeImpl *node ) {
    return (node && node->renderer() ? innerPart( node->renderer() ) : 0);
}
