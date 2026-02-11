process_tetrahedra
          ( Field field, hash_table_rec *htab, InvalidComponentHandle i_handle )
{
    Tetrahedron *tetras_ptr;
    char      invalid = 0;
    int	      nt;
    int	      i;


    if ( ERROR == _dxf_GetComponentData( (Object)field,
                                         TETRA_CONNECTIONS_COMP,
                                         &nt, NULL, NULL,
                                         (Pointer *) &tetras_ptr ) )
        goto error;

    for ( i=0; i<nt; i++, tetras_ptr++ )
    {
        invalid = (i_handle==NULL)? 0 :
                  DXIsElementInvalidSequential ( i_handle, i );

        if ( !store_hash ( htab, tetras_ptr->p, tetras_ptr->q, invalid ) ||
             !store_hash ( htab, tetras_ptr->p, tetras_ptr->r, invalid ) ||
             !store_hash ( htab, tetras_ptr->p, tetras_ptr->s, invalid ) ||
             !store_hash ( htab, tetras_ptr->q, tetras_ptr->r, invalid ) ||
             !store_hash ( htab, tetras_ptr->r, tetras_ptr->s, invalid ) ||
             !store_hash ( htab, tetras_ptr->s, tetras_ptr->q, invalid )   )
            goto error;
    }

    return OK;

    error:
        DXASSERT ( DXGetError() != ERROR_NONE );
        return ERROR;
}
