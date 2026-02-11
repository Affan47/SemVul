DoubleTriangle( void )
{
   tVertex  v0, v1, v2, v3;
   tFace    f0, f1 = NULL;
   int      vol;


   v0 = vertices;
   while ( Collinear( v0, v0->next, v0->next->next ) )
      if ( ( v0 = v0->next ) == vertices ) {
         std::cout << "DoubleTriangle:  All points are Collinear!\n" ;
	 exit(0);
      }
   v1 = v0->next;
   v2 = v1->next;


   v0->mark = PROCESSED;
   v1->mark = PROCESSED;
   v2->mark = PROCESSED;


   f0 = MakeFace( v0, v1, v2, f1 );
   f1 = MakeFace( v2, v1, v0, f0 );
   f0->fNum = fcount++;
   f1->fNum = f0->fNum;


   f0->edge[0]->adjface[1] = f1;
   f0->edge[1]->adjface[1] = f1;
   f0->edge[2]->adjface[1] = f1;
   f1->edge[0]->adjface[1] = f0;
   f1->edge[1]->adjface[1] = f0;
   f1->edge[2]->adjface[1] = f0;


   v3 = v2->next;
   vol = VolumeSign( f0, v3 );
   while ( !vol )   {
      if ( ( v3 = v3->next ) == v0 ) {
         std::cout << "DoubleTriangle:  All points are coplanar!\n";
	 exit(0);
      }
      vol = VolumeSign( f0, v3 );
   }


   vertices = v3;
   if ( debug ) {
      std::cerr << "DoubleTriangle: finished. Head repositioned at v3.\n" ;
      PrintOut( vertices );
   }


}
