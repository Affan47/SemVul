math_buttons_load_finc_dialogs (MathButtons* self) {
	g_return_if_fail (self != NULL);
	math_buttons_load_finc_dialog (self, "ctrm_dialog", MATH_BUTTONS_ctrm_entries, G_N_ELEMENTS (MATH_BUTTONS_ctrm_entries), FINANCIAL_DIALOG_CTRM_DIALOG);
	math_buttons_load_finc_dialog (self, "ddb_dialog", MATH_BUTTONS_ddb_entries, G_N_ELEMENTS (MATH_BUTTONS_ddb_entries), FINANCIAL_DIALOG_DDB_DIALOG);
	math_buttons_load_finc_dialog (self, "fv_dialog", MATH_BUTTONS_fv_entries, G_N_ELEMENTS (MATH_BUTTONS_fv_entries), FINANCIAL_DIALOG_FV_DIALOG);
	math_buttons_load_finc_dialog (self, "gpm_dialog", MATH_BUTTONS_gpm_entries, G_N_ELEMENTS (MATH_BUTTONS_gpm_entries), FINANCIAL_DIALOG_GPM_DIALOG);
	math_buttons_load_finc_dialog (self, "pmt_dialog", MATH_BUTTONS_pmt_entries, G_N_ELEMENTS (MATH_BUTTONS_pmt_entries), FINANCIAL_DIALOG_PMT_DIALOG);
	math_buttons_load_finc_dialog (self, "pv_dialog", MATH_BUTTONS_pv_entries, G_N_ELEMENTS (MATH_BUTTONS_pv_entries), FINANCIAL_DIALOG_PV_DIALOG);
	math_buttons_load_finc_dialog (self, "rate_dialog", MATH_BUTTONS_rate_entries, G_N_ELEMENTS (MATH_BUTTONS_rate_entries), FINANCIAL_DIALOG_RATE_DIALOG);
	math_buttons_load_finc_dialog (self, "sln_dialog", MATH_BUTTONS_sln_entries, G_N_ELEMENTS (MATH_BUTTONS_sln_entries), FINANCIAL_DIALOG_SLN_DIALOG);
	math_buttons_load_finc_dialog (self, "syd_dialog", MATH_BUTTONS_syd_entries, G_N_ELEMENTS (MATH_BUTTONS_syd_entries), FINANCIAL_DIALOG_SYD_DIALOG);
	math_buttons_load_finc_dialog (self, "term_dialog", MATH_BUTTONS_term_entries, G_N_ELEMENTS (MATH_BUTTONS_term_entries), FINANCIAL_DIALOG_TERM_DIALOG);
}
