ffchfl( fitsfile *fptr, int *status)
{
   int nblank,i,gotend;
   LONGLONG endpos;
   char rec[FLEN_CARD];
   char *blanks="                                                                                ";

   if( *status > 0 ) return (*status);


    if (fptr->HDUposition != (fptr->Fptr)->curhdu)
        ffmahd(fptr, (fptr->HDUposition) + 1, NULL, status);


   endpos=(fptr->Fptr)->headend;
   nblank=(long) (((fptr->Fptr)->datastart-endpos)/80);


   ffmbyt(fptr,endpos,TRUE,status);


   gotend=FALSE;
   for(i=0;i<nblank;i++) {
      ffgbyt(fptr,80,rec,status);
      if( !strncmp(rec, "END     ", 8) ) {
         if( gotend ) {

            *status=BAD_HEADER_FILL;
            ffpmsg("Warning: Header fill area contains duplicate END card:");
         }
         gotend=TRUE;
         if( strncmp( rec+8, blanks+8, 72) ) {

            *status=END_JUNK;
            ffpmsg(
            "Warning: END keyword contains extraneous non-blank characters:");
         }
      } else if( gotend ) {
         if( strncmp( rec, blanks, 80 ) ) {

            *status=BAD_HEADER_FILL;
            ffpmsg(
         "Warning: Header fill area contains extraneous non-blank characters:");
         }
      }

      if( *status > 0 ) {
         rec[FLEN_CARD - 1] = '\0';
         ffpmsg(rec);
         return( *status );
      }
   }
   return( *status );
}
