config_values_free( FusionVector *vector )
{
     char *value;
     int   i;

     fusion_vector_foreach (value, i, *vector)
          D_FREE( value );

     fusion_vector_destroy( vector );
     fusion_vector_init( vector, 2, NULL );
}
