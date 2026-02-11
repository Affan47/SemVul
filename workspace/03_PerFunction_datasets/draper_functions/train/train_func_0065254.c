setElementAt ( CMPIArray * array, CMPICount index, CMPIValue * val,
       CMPIType type, int opt )
{
   struct native_array * a = (struct native_array *) array;

   if ( a->dynamic && index == a->size ) {
      native_array_increase_size(array, 1);
   }

   if ( index < a->size ) {
      CMPIValue v;
      v.string=NULL;

      if ( type == CMPI_chars && a->type == CMPI_string ) {
	 if (val) {
	     v.string = native_new_CMPIString ( (char *) val->chars, NULL );
	     type = CMPI_string;
	     val  = &v;
	 } else {
	     type = CMPI_null;
	 }
      }

      if ( type == CMPI_null ) {

         if ( ! ( a->data[index].state & CMPI_nullValue ) ) {
            __make_NULL ( a, index, index, 1 );
         }
         CMReturn ( CMPI_RC_OK );
      }

      if ( opt || type == a->type ) {

         CMPIStatus rc = {CMPI_RC_OK, NULL};

         a->data[index].state = 0;
	 a->data[index].value = (opt) ?
			 *val : native_clone_CMPIValue ( type, val, &rc );
         if(v.string)
         	CMRelease(v.string);
         return rc;
      }
   }
   CMReturn ( CMPI_RC_ERR_FAILED );
}
