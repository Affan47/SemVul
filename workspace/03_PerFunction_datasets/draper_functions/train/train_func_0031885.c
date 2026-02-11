addClassMethodQualifier( CMPIConstClass* cc, char * mname, char *qname,
                     CMPIValue * value,
                     CMPIType type)
{
   struct native_constClass * c = (struct native_constClass *) cc;
   struct native_method *m=methodFT.getMethod ( c->methods, mname );

   if (m) {
     if ( qualifierFT.setQualifier ( m->qualifiers,
                     qname,
                     type,
                     value ) ) {
        qualifierFT.addQualifier ( &m->qualifiers,
                     qname,
                     type,
                     0,
                     value );
     }
     return ( CMPI_RC_OK );
   }
   return CMPI_RC_ERR_METHOD_NOT_FOUND;
}
