import_base_rule( void * r_, void * d_ )
{
    RULE * r = (RULE *)r_;
    RULE * ir1;
    RULE * ir2;
    struct import_base_data * d = (struct import_base_data *)d_;
    OBJECT * qname;

    string qualified_name[ 1 ];
    string_new      ( qualified_name                             );
    string_append   ( qualified_name, object_str( d->base_name ) );
    string_push_back( qualified_name, '.'                        );
    string_append   ( qualified_name, object_str( r->name )      );
    qname = object_new( qualified_name->value );
    string_free( qualified_name );

    ir1 = import_rule( r, d->class_module, r->name );
    ir2 = import_rule( r, d->class_module, qname );

    object_free( qname );


    ir1->exported = ir2->exported = r->exported;


    if ( ( r->module == d->base_module ) || ( r->module->class_module &&
        ( r->module->class_module == d->base_module ) ) )
    {
        rule_localize( ir1, d->class_module );
        rule_localize( ir2, d->class_module );
    }
}
