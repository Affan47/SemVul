control_config_common_init()
{
	for (int i=0; i<CCFG_MAX; i++)
		Control_config[i].disabled = false;

    control_config_common_load_overrides();
	if(Lcl_gr){
		Scan_code_text = Scan_code_text_german;
		Joy_button_text = Joy_button_text_german;


		Control_config[TARGET_SHIP_IN_RETICLE].key_default = KEY_Z;
		Control_config[TARGET_LAST_TRANMISSION_SENDER].key_default = KEY_ALTED | KEY_Z;
		Control_config[REVERSE_THRUST].key_default = KEY_Y;
		Control_config[DISARM_MESSAGE].key_default = KEY_SHIFTED | KEY_Y;
	} else if(Lcl_fr){
		Scan_code_text = Scan_code_text_french;
		Joy_button_text = Joy_button_text_french;
	} else {
		Scan_code_text = Scan_code_text_english;
		Joy_button_text = Joy_button_text_english;
	}
}
