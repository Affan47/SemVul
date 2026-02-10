syck_map_add_m(VALUE self, VALUE key, VALUE val)
{
    SyckNode *node;
    VALUE emitter = rb_ivar_get( self, s_emitter );
    Data_Get_Struct( self, SyckNode, node );

    if ( rb_respond_to( emitter, s_node_export ) ) {
        key = rb_funcall( emitter, s_node_export, 1, key );
        val = rb_funcall( emitter, s_node_export, 1, val );
    }
    syck_map_add( node, key, val );
    rb_hash_aset( rb_ivar_get( self, s_value ), key, val );

    return self;
}
