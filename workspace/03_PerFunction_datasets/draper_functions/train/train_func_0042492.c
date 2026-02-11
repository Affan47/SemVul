GetNumber(unsigned int start, int len)
	{
		if (len == -1)
			len = m_len - start;
		if (len < 1)
			return -1;

		if (start + static_cast<unsigned int>(len) > m_len)
			return -1;

		if (m_pToken[start] < '0' || m_pToken[start] > '9')
			return -1;

		wxLongLong number = 0;
		for (unsigned int i = start; i < (start + len); ++i)
		{
			if (m_pToken[i] < '0' || m_pToken[i] > '9')
				break;
			number *= 10;
			number += m_pToken[i] - '0';
		}
		return number;
	}
