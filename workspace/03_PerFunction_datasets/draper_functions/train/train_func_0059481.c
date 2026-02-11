LoadMesh( const char *pFile ) {
    char *json_file = NULL;
    cJSON *root = NULL;
    int handle = -1;


    Byte_ReadFile( &json_file, pFile );
    check( json_file, " " );

    root = cJSON_Parse( json_file );
    check( root, "JSON parse error [%s] before :\n%s\n", pFile, cJSON_GetErrorPtr() );

    cJSON *positions = cJSON_GetObjectItem( root, "positions" );
    cJSON *texcoords = cJSON_GetObjectItem( root, "texcoords" );
    cJSON *indices = cJSON_GetObjectItem( root, "indices" );

    check( positions && texcoords , "Invalid mesh file. Needs positions and texcoords!\n" );


    vec2 *positions_v = NULL, *texcoords_v = NULL;
    u32 *indices_v = NULL;

    int position_n = cJSON_GetArraySize( positions );
    positions_v = byte_alloc( position_n * sizeof( vec2 ) );
    texcoords_v = byte_alloc( position_n * sizeof( vec2 ) );

    for( int i = 0; i < position_n; ++i ) {
        cJSON *pos = cJSON_GetArrayItem( positions, i );
        cJSON *tex = cJSON_GetArrayItem( texcoords, i );

        vec2 pos_v = { cJSON_GetArrayItem( pos, 0 )->valuedouble, cJSON_GetArrayItem( pos, 1 )->valuedouble };
        positions_v[i] = pos_v;

        vec2 tex_v = { cJSON_GetArrayItem( tex, 0 )->valuedouble, cJSON_GetArrayItem( tex, 1 )->valuedouble };
        texcoords_v[i] = tex_v;
    }


    int indice_n = 0;
    if( indices ) {
        indice_n = cJSON_GetArraySize( indices );
        indices_v = byte_alloc( indice_n * sizeof( u32 ) );

        for( int i = 0; i < indice_n; ++i ) {
            indices_v[i] = cJSON_GetArrayItem( indices, i )->valuedouble;
        }
    }


    handle = Renderer_createStaticMesh( ETriangles, indices_v, indice_n * sizeof( u32 ), positions_v, position_n * sizeof( vec2 ), texcoords_v, position_n * sizeof( vec2 ) );
    check( handle >= 0, "Error while creating mesh!\n" );

error:
    DEL_PTR( json_file );
    DEL_PTR( positions_v );
    DEL_PTR( texcoords_v );
    DEL_PTR( indices_v );
    if( root ) cJSON_Delete( root );
    return handle;
}
