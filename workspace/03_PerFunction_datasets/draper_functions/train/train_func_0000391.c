IsCommentFiltered(const wxString& comment)
{
	if (s_FilterComments) {
		wxStringTokenizer tokenizer( s_CommentFilterString, wxT(",") );
		while (tokenizer.HasMoreTokens()) {
			if ( comment.Lower().Trim(false).Trim(true).Contains(
					tokenizer.GetNextToken().Lower().Trim(false).Trim(true))) {
				return true;
			}
		}
	}
	return false;
}
