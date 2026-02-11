clone_rv( SV * source ) {
	SV *  clone;

	TRACE( ( "Ripping reference from source\n" ) );

	if ( ! SvROK( source ) ) {
		clone = SvREFCNT_inc( source );
		SV_TRIAGE( source, clone );
		return clone;
	}
	else {
		clone = newSV(0);
		SvUPGRADE( clone, SVt_RV );
		SV_TRIAGE( source, clone );
	}

	SvROK_on( clone );
	SvRV( clone ) = sv_clone( SvRV( source ) );

	if ( sv_isobject( source ) )
		SV_HOOK_OBJECT( source, clone );

	return clone;
}
