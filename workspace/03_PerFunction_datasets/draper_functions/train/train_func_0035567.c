OnViewFiles( wxCommandEvent& WXUNUSED(event) )
{
	ItemList sources = ::GetSelectedItems( this );

	if ( sources.size() == 1 ) {
		sources.front()->GetSource().RequestSharedFileList();
	}
}
