RemoveKeyword(const wxString& keyword, CKnownFile *file)
{
	CKeyWordList::iterator pos;
	CPublishKeyword* pubKw = FindKeyword(keyword, &pos);
	if (pubKw != NULL) {
		if (pubKw->RemoveRef(file) == 0) {
			if (pos == m_posNextKeyword) {
				++m_posNextKeyword;
			}
			m_lstKeywords.erase(pos);
			delete pubKw;
			SetNextPublishTime(0);
		}
	}
}
