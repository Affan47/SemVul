get() {
	if (m_Sub < m_Max) {
		return m_Unicode[m_Sub++];
	} else if (m_Pos >= m_Str->length()) {
		return 0;
	} else {
		m_Sub = 0;
		unsigned int unicode = m_Str->get(m_Pos++);
		if (unicode < 0x80) {
			m_Max = 0;
			return (char)unicode;
		} else if (unicode < 0x800) {
			m_Max = 1;
			m_Unicode[0] = 0x80 | (unicode & 0x3F);
			return 0xC0 | ((unicode >> 6) & 0x1F);
		} else if (unicode < 0x10000) {
			m_Max = 2;
			m_Unicode[0] = 0x80 | ((unicode >> 6) & 0x3F);
			m_Unicode[1] = 0x80 | (unicode & 0x3F);
			return 0xE0 | ((unicode >> 12) & 0xF);
		} else if (unicode < 0x200000) {
			m_Max = 3;
			m_Unicode[0] = 0x80 | ((unicode >> 12) & 0x3F);
			m_Unicode[1] = 0x80 | ((unicode >> 6) & 0x3F);
			m_Unicode[2] = 0x80 | (unicode & 0x3F);
			return 0xF0 | ((unicode >> 18) & 0x7);
		} else if (unicode < 0x4000000) {
			m_Max = 4;
			m_Unicode[0] = 0x80 | ((unicode >> 18) & 0x3F);
			m_Unicode[1] = 0x80 | ((unicode >> 12) & 0x3F);
			m_Unicode[2] = 0x80 | ((unicode >> 6) & 0x3F);
			m_Unicode[3] = 0x80 | (unicode & 0x3F);
			return 0xF8 | ((unicode >> 24) & 0x3);
		} else {
			m_Max = 5;
			m_Unicode[0] = 0x80 | ((unicode >> 24) & 0x3F);
			m_Unicode[1] = 0x80 | ((unicode >> 18) & 0x3F);
			m_Unicode[2] = 0x80 | ((unicode >> 12) & 0x3F);
			m_Unicode[3] = 0x80 | ((unicode >> 6) & 0x3F);
			m_Unicode[4] = 0x80 | (unicode & 0x3F);
			return 0xFC | ((unicode >> 30) & 0x1);
		}
		return 0;
	}
}
