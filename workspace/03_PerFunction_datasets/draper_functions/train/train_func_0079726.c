SetFileCommentRating(const wxString& strNewComment, int8 iNewRating)
{
	if (m_strComment != strNewComment || m_iRating != iNewRating) {
		SetLastPublishTimeKadNotes(0);
		wxString strCfgPath = wxT("/") + m_abyFileHash.Encode() + wxT("/");

		wxConfigBase* cfg = wxConfigBase::Get();
		if (strNewComment.IsEmpty() && iNewRating == 0) {
			cfg->DeleteGroup(strCfgPath);
		} else {
			cfg->Write( strCfgPath + wxT("Comment"), strNewComment);
			cfg->Write( strCfgPath + wxT("Rate"), (int)iNewRating);
		}

		m_strComment = strNewComment;
 		m_iRating = iNewRating;

		SourceSet::iterator it = m_ClientUploadList.begin();
		for ( ; it != m_ClientUploadList.end(); it++ ) {
			it->SetCommentDirty();
		}
	}
}
