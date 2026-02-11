GetImage(const wxString &name)
{
	ImageMap::iterator it = m_image_map.find(name);
	if (it != m_image_map.end()) {
		return it->second;
	}
	wxFileName filename(m_image_dir + name);
	CFileImage *fimg = new CFileImage(filename.GetFullPath());
	if ( fimg->OpenOk() ) {
		m_image_map[name] = fimg;
		return fimg;
	} else {
		delete fimg;
		return 0;
	}
}
