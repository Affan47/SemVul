AddED2KLink( const wxString& link, uint8 category )
{
	wxASSERT( !link.IsEmpty() );
	wxString URI = link;


	if ( URI.Last() != wxT('/') ) {
		URI += wxT("/");
	}

	try {
		CScopedPtr<CED2KLink> uri(CED2KLink::CreateLinkFromUrl(URI));

		return AddED2KLink( uri.get(), category );
	} catch ( const wxString& err ) {
		AddLogLineC(CFormat( _("Invalid eD2k link! ERROR: %s")) % err);
	}

	return false;
}
