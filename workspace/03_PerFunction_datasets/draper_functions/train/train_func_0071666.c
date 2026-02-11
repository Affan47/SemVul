Update(const wxString& strURL)
{
	if (!strURL.IsEmpty()) {
		m_URL = strURL;

		wxString filename = theApp->ConfigDir + wxT("ipfilter.download");
		wxString oldfilename = theApp->ConfigDir + wxT("ipfilter.dat");
		CHTTPDownloadThread *downloader = new CHTTPDownloadThread(m_URL, filename, oldfilename, HTTP_IPFilter, true, true);

		downloader->Create();
		downloader->Run();
	}
}
