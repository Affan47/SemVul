CreateED2kLink(const CAbstractFile *f, bool add_source, bool use_hostname, bool addcryptoptions)
{
	wxASSERT(!(!add_source && (use_hostname || addcryptoptions)));

	wxString strURL = CFormat(wxT("ed2k://|file|%s|%i|%s|/"))
		% f->GetFileName().Cleanup(false)
		% f->GetFileSize() % f->GetFileHash().Encode();

	if (add_source && theApp->IsConnected() && !theApp->IsFirewalled()) {

		strURL << wxT("|sources,");
		if (use_hostname) {
			strURL << thePrefs::GetYourHostname();
		} else {
			uint32 clientID = theApp->GetID();
			strURL = CFormat(wxT("%s%u.%u.%u.%u"))
				% strURL
				% (clientID & 0xff)
				% ((clientID >> 8) & 0xff)
				% ((clientID >> 16) & 0xff)
				% ((clientID >> 24) & 0xff);
		}

 		strURL << wxT(":") <<
			thePrefs::GetPort();

		if (addcryptoptions) {
			uint8 uSupportsCryptLayer = thePrefs::IsClientCryptLayerSupported() ? 1 : 0;
			uint8 uRequestsCryptLayer = thePrefs::IsClientCryptLayerRequested() ? 1 : 0;
			uint8 uRequiresCryptLayer = thePrefs::IsClientCryptLayerRequired() ? 1 : 0;
			uint16 byCryptOptions = (uRequiresCryptLayer << 2) | (uRequestsCryptLayer << 1) | (uSupportsCryptLayer << 0) | (uSupportsCryptLayer ? 0x80 : 0x00);

			strURL << wxT(":") << byCryptOptions;

			if (byCryptOptions & 0x80) {
				strURL << wxT(":") << thePrefs::GetUserHash().Encode();
			}
		}
		strURL << wxT("|/");
	} else if (add_source) {
		AddLogLineC(_("WARNING: You can't add yourself as a source for an eD2k link while having a lowid."));
	}


	return strURL;
}
