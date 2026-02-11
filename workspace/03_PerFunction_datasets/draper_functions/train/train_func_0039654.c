GetRecnoKey(pTHX_ DB_File db, I32 value)
#else
GetRecnoKey(db, value)
DB_File  db ;
I32      value ;
#endif
{
    if (value < 0) {

	I32 length = GetArrayLength(aTHX_ db) ;


	if (length + value + 1 <= 0) {
            tidyUp(db);
	    croak("Modification of non-creatable array value attempted, subscript %ld", (long)value) ;
	}

	value = length + value + 1 ;
    }
    else
        ++ value ;

    return value ;
}
