escapize_string( const char * str )
{
   int ii,jj , lstr,lout ;
   char *out ;

   if( str == NULL || (lstr=(int)strlen(str)) == 0 ){
     out = nifti_strdup("''") ; return out ;
   }

   lout = 4 ;
   for( ii=0 ; ii < lstr ; ii++ ){
     switch( str[ii] ){
       case '&':  lout += 5 ; break ;

       case '<':
       case '>':  lout += 4 ; break ;

       case '"' :
       case '\'': lout += 6 ; break ;

       case CR:
       case LF:   lout += 6 ; break ;


       default: lout++ ; break ;
     }
   }
   out = (char *)calloc(1,lout) ;
   if( !out ){
      fprintf(stderr,"** escapize_string: failed to alloc %d bytes\n",lout);
      return NULL;
   }
   out[0] = '\'' ;
   for( ii=0,jj=1 ; ii < lstr ; ii++ ){
      switch( str[ii] ){
         default: out[jj++] = str[ii] ; break ;

         case '&':  memcpy(out+jj,"&amp;",5)  ; jj+=5 ; break ;

         case '<':  memcpy(out+jj,"&lt;",4)   ; jj+=4 ; break ;
         case '>':  memcpy(out+jj,"&gt;",4)   ; jj+=4 ; break ;

         case '"' : memcpy(out+jj,"&quot;",6) ; jj+=6 ; break ;

         case '\'': memcpy(out+jj,"&apos;",6) ; jj+=6 ; break ;

         case CR:   memcpy(out+jj,"&#x0d;",6) ; jj+=6 ; break ;
         case LF:   memcpy(out+jj,"&#x0a;",6) ; jj+=6 ; break ;
      }
   }
   out[jj++] = '\''  ;
   out[jj]   = '\0' ;
   return out ;
}
