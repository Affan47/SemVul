_prefsListener( XAP_Prefs *pPrefs, UT_StringPtrMap * , void *data )
{
	AP_LeftRuler *pLeftRuler = static_cast<AP_LeftRuler *>(data);
	UT_ASSERT( data && pPrefs );

	const gchar *pszBuffer;
	pPrefs->getPrefsValue(static_cast<const gchar *>(AP_PREF_KEY_RulerUnits), &pszBuffer );


	UT_Dimension dim = UT_determineDimension( pszBuffer, DIM_none );
	UT_ASSERT( dim != DIM_none );

	if ( dim != pLeftRuler->getDimension() )
		pLeftRuler->setDimension( dim );
}
