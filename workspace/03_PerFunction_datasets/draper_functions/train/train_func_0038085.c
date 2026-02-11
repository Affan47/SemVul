Sprite_load( Sprite *s, const char *file ) {
    cJSON *root = NULL, *item = NULL;
    char *json_file = NULL;
    bool return_val = false;

    if( s && file ) {

        Byte_ReadFile( &json_file, file );
        check( json_file, "Error while loading sprite!\n" );

        root = cJSON_Parse( json_file );
        check( root, "JSON parse error [%s] before :\n%s\n", file, cJSON_GetErrorPtr() );


        s->position = (vec2){0,0};
        s->depth = 0;
        s->used_sprite = -1;
        s->animation = NULL;


        item = cJSON_GetObjectItem( root, "width" );
        check( item, "Error while loading sprite '%s', need entry 'width'.\n", file );

        s->mesh_size.x = item->valueint;

        item = cJSON_GetObjectItem( root, "height" );
        check( item, "Error while loading sprite '%s', need entry 'height'.\n", file );

        s->mesh_size.y = item->valueint;


        item = cJSON_GetObjectItem( root, "texture" );
        s->tex_n = cJSON_GetArraySize( item );
        check( s->tex_n > 0, "Error while loading sprite '%s', need entry(array) 'texture'.\n", file );

        for( int i = 0; i < s->tex_n; ++i ) {
            cJSON *tex = cJSON_GetArrayItem( item, i );
            if( tex ) {
                const char *tex_s = tex->valuestring;


                s->tex_id[i] = ResourceManager_get( tex_s );
                check( s->tex_id[i] >= 0, "Error while loading sprite '%s' texture. Texture '%s' is not a loaded resource.\n", file, tex_s );
            }
        }


        s->texcoords_size = (vec2){ s->mesh_size.x / 2048, s->mesh_size.y / 2048 };


        str256 scaled_mesh_str;
        str16 mesh_size;
        snprintf( mesh_size, 16, "%d.%d", (int)s->mesh_size.x, (int)s->mesh_size.y );

        strcpy( scaled_mesh_str, "quadmesh.json" );
        strcat( scaled_mesh_str, mesh_size );

        s->mesh_id = ResourceManager_get( scaled_mesh_str );


        if( -1 == s->mesh_id ) {
            s->mesh_id = ResourceManager_get( "quadmesh.json" );
            check( s->mesh_id >= 0, "Error while loading sprite '%s' mesh. Mesh 'quadmesh.json' is not a loaded resource.\n", file );


            int scaled_mesh = Renderer_createRescaledMesh( s->mesh_id, &s->mesh_size, &s->texcoords_size );
            check( scaled_mesh >= 0, "Error while creating scaled mesh for sprite '%s'. \n", file );

            s->mesh_id = scaled_mesh;


            ResourceManager_add( scaled_mesh_str, scaled_mesh );
        }

        return_val = true;
    }

error:
    DEL_PTR( json_file );
    if( root ) cJSON_Delete( root );
    return return_val;
}
