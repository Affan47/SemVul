apply_iscsi_settings ( void ) {
	struct iscsi_string_setting *setting;
	unsigned int i;
	int rc;

	for ( i = 0 ; i < ( sizeof ( iscsi_string_settings ) /
			    sizeof ( iscsi_string_settings[0] ) ) ; i++ ) {
		setting = &iscsi_string_settings[i];
		if ( ( rc = apply_iscsi_string_setting ( setting ) ) != 0 ) {
			DBG ( "iSCSI could not apply setting %s\n",
			      setting->setting->name );
			return rc;
		}
	}

	return 0;
}
