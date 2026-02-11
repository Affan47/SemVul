bench_property( void )
{
     DirectResult   ret;
     FusionProperty property;

     ret = fusion_property_init( &property, world );
     if (ret) {
          fprintf( stderr, "Fusion Error %d\n", ret );
          return;
     }


     BENCH_START();

     BENCH_LOOP() {
          fusion_property_lease( &property );
          fusion_property_cede( &property );
     }

     BENCH_STOP();

     printf( "property lease/cede                   -> %8.2f k/sec\n", BENCH_RESULT() );


     fusion_property_destroy( &property );

     printf( "\n" );
}
