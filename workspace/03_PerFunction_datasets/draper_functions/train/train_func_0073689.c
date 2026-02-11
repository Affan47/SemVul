Do_GTI( Node *this )
{
   Node *theExpr, *theTimes;
   double *start, *stop, *times;
   long elem, nGTI, gti;
   int ordered;

   theTimes = gParse.Nodes + this->SubNodes[0];
   theExpr  = gParse.Nodes + this->SubNodes[1];

   nGTI    = theTimes->value.nelem;
   start   = theTimes->value.data.dblptr;
   stop    = theTimes->value.data.dblptr + nGTI;
   ordered = theTimes->type;

   if( theExpr->operation==CONST_OP ) {

      this->value.data.log =
	 (Search_GTI( theExpr->value.data.dbl, nGTI, start, stop, ordered )>=0);
      this->operation      = CONST_OP;

   } else {

      Allocate_Ptrs( this );

      times = theExpr->value.data.dblptr;
      if( !gParse.status ) {

	 elem = gParse.nRows * this->value.nelem;
	 if( nGTI ) {
	    gti = -1;
	    while( elem-- ) {
	       if( (this->value.undef[elem] = theExpr->value.undef[elem]) )
		  continue;


	       if( gti<0 || times[elem]<start[gti] || times[elem]>stop[gti] ) {
		  gti = Search_GTI( times[elem], nGTI, start, stop, ordered );
	       }
	       this->value.data.logptr[elem] = ( gti>=0 );
	    }
	 } else
	    while( elem-- ) {
	       this->value.data.logptr[elem] = 0;
	       this->value.undef[elem]       = 0;
	    }
      }
   }

   if( theExpr->operation>0 )
      free( theExpr->value.data.ptr );
}
