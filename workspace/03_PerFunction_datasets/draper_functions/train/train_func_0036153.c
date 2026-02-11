compiler_free( compiler * c )
{
    int i;
    dynamic_array_free( c->actions );
    dynamic_array_free( c->rules );
    for ( i = 0; i < c->labels->size; ++i )
        dynamic_array_free( dynamic_array_at( struct label_info, c->labels, i
            ).uses );
    dynamic_array_free( c->labels );
    dynamic_array_free( c->constants );
    dynamic_array_free( c->code );
}
