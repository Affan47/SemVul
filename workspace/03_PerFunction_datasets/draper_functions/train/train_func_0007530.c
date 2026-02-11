SetExArtProvider()
{
	SetArtProvider(new wxAuiTabArtEx(this, (GetWindowStyle() & wxAUI_NB_BOTTOM) != 0, new struct wxAuiTabArtExData));
}
