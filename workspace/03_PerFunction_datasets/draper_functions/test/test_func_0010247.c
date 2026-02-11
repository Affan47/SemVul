dsgw_get_values( LDAP *ld, LDAPMessage *entry,
		 const char *target )
{
    BerElement  *ber        = NULL;
    char        *attr       = NULL;
    char        *new_target = NULL;
    int          new_target_size = 0;
    struct berval **val_youse  = NULL;
    struct berval **temp_vals  = NULL;
    int          i          = 0;
    int          j          = 0;
    int          temp_val_count = 0;


    new_target = (char *) dsgw_ch_malloc (sizeof(char) * (strlen(target) + 2) );
    sprintf (new_target, "%s;", target);

    new_target_size = strlen(new_target);


    for ( attr = ldap_first_attribute( ld, entry, &ber ); attr != NULL;
	  attr = ldap_next_attribute( ld, entry, ber ) ) {


	if ( strcasecmp(attr, target) == 0 ||
	     strncasecmp (attr, new_target, new_target_size) == 0) {
	    temp_vals =  ldap_get_values_len( ld, entry, attr );

	    if (temp_vals == NULL) {
		continue;
	    }


	    if (val_youse) {
		for (; val_youse[i] && val_youse[i]->bv_val; i++) ;
	    }


	    for (temp_val_count = 0; temp_vals[temp_val_count] != NULL;
		 temp_val_count++);


	    val_youse = (struct berval **) dsgw_ch_realloc (val_youse, sizeof(struct berval *) * (temp_val_count + i + 1) );


	    for (j = 0; j < temp_val_count; j++, i++) {
		val_youse[i] = temp_vals[j];
	    }

	    val_youse[i] = NULL;

	    ldap_memfree(temp_vals);

	}
    }


    if ( ber != NULL ) {

	ber_free( ber, 0 );

    }

    free (new_target);

    return(val_youse);
}
