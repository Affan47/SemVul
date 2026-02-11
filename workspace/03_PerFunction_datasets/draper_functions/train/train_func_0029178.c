RenameFile(CKnownFile* file, const CPath& newName)
{
	if (file->IsPartFile()) {
		CPartFile* pfile = dynamic_cast<CPartFile*>(file);

		if (file->GetStatus() != PS_COMPLETING) {
			pfile->SetFileName(newName);
			pfile->SavePartFile();

			Notify_SharedFilesUpdateItem(file);
			Notify_DownloadCtrlUpdateItem(file);

			return true;
		}
	} else {
		CPath oldPath = file->GetFilePath().JoinPaths(file->GetFileName());
		CPath newPath = file->GetFilePath().JoinPaths(newName);

		if (CPath::RenameFile(oldPath, newPath)) {


			Kademlia::WordList oldwords = file->GetKadKeywords();
			file->SetFileName(newName);
			theApp->knownfiles->Save();
			UpdateItem(file);
			RepublishFile(file);

			const Kademlia::WordList& newwords = file->GetKadKeywords();
			Kademlia::WordList::iterator itold;
			Kademlia::WordList::const_iterator itnew;

			for (itnew = newwords.begin(); itnew != newwords.end(); ++itnew) {
				for (itold = oldwords.begin(); itold != oldwords.end(); ++itold) {
					if (*itold == *itnew) {
						break;
					}
				}
				if (itold != oldwords.end()) {

					oldwords.erase(itold);
				} else {

					m_keywords->AddKeyword(*itnew, file);
				}
			}

			for (itold = oldwords.begin(); itold != oldwords.end(); ++itold) {
				m_keywords->RemoveKeyword(*itold, file);
			}

			Notify_DownloadCtrlUpdateItem(file);
			Notify_SharedFilesUpdateItem(file);

			return true;
		}
	}

	return false;
}
