fusion_vector_remove( FusionVector *vector,
                      int           index )
{
     D_MAGIC_ASSERT( vector, FusionVector );
     D_ASSERT( index >= 0 );
     D_ASSERT( index < vector->count );


     memmove( &vector->elements[ index ],
              &vector->elements[ index + 1 ],
              (vector->count - index - 1) * sizeof(void*) );


     vector->count--;

     return DR_OK;
}
