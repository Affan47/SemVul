CreateItem(const CEC_SearchFile_Tag *tag)
#endif

{
	CSearchFile *file = new CSearchFile(tag);
	ProcessItemUpdate(tag, file);

	theApp->amuledlg->m_searchwnd->AddResult(file);

	return file;
}
