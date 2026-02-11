Concat(const CLine *pLine) const
	{
		int newLen = m_len + pLine->m_len + 1;
		wxChar* p = new wxChar[newLen];
		memcpy(p, m_pLine, m_len * sizeof(wxChar));
		p[m_len] = ' ';
		memcpy(p + m_len + 1, pLine->m_pLine, pLine->m_len * sizeof(wxChar));

		return new CLine(p, m_len + pLine->m_len + 1, pLine->m_trailing_whitespace);
	}
