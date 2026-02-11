Add()
{

	U32 savePos = m_pos;


	U16 tagCode;
	U32 tagLen;
	bool ok = ParseTagHeader(&tagCode, &tagLen);
	if (!ok) {
		return false;
	}


	if (tagCode == FILE_ATTRS_TAG_TYPE) {

		savePos = m_pos;


		U32 flags = GetDWord();


		if (flags & USE_NETWORK_FLAG_MASK) {
			printf("%s already has network privileges. Not modifying.\n",
				   m_path);
			return false;
		} else {

			flags |= USE_NETWORK_FLAG_MASK;
			m_pos = savePos;
			PutDWord(flags);

			m_bChanges = true;
			snprintf(m_successMsgBuf, SUCCESS_MSG_SIZE,
					 "Network privileges added to %s\n", m_path);
			return true;
		}
	} else {


		m_pos = savePos;


		U8 *pSrc = (m_pBuf + m_len - 1);
		U8 *pDst = (pSrc + 6);

		for (U32 i = (m_len - 1); (i >= m_pos); i--) {
			*pDst-- = *pSrc--;
		}


		U16 newHeader = ((U16)FILE_ATTRS_TAG_TYPE << 6);
		newHeader |= (U16)4;
		PutWord(newHeader);


		U32 flags = USE_NETWORK_FLAG_MASK;
		PutDWord(flags);


		m_len += 6;
		m_bChanges = true;

		snprintf(m_successMsgBuf, SUCCESS_MSG_SIZE,
				 "Network privileges added to %s\n", m_path);
		return true;
	}
}
