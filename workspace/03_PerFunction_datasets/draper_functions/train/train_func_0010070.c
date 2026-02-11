rewrite_casestring
#ifdef KC_USE_PROTOTYPES
(casestring kc_p, rview kc_current_view)
#else
(kc_p, kc_current_view) casestring kc_p; rview kc_current_view;
#endif
{

	assert_casestring( kc_p, "kc_p" );
	return kc_p;
}
