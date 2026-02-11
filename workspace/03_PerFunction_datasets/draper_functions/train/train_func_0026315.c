SHPDestroyObject( SHPObject * psShape )

{
    if( psShape == NULL )
        return;

    if( psShape->padfX != NULL )
        free( psShape->padfX );
    if( psShape->padfY != NULL )
        free( psShape->padfY );
    if( psShape->padfZ != NULL )
        free( psShape->padfZ );
    if( psShape->padfM != NULL )
        free( psShape->padfM );

    if( psShape->panPartStart != NULL )
        free( psShape->panPartStart );
    if( psShape->panPartType != NULL )
        free( psShape->panPartType );

    free( psShape );
}
