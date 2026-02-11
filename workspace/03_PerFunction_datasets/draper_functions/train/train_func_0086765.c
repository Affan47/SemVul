getVnCharset(int charsetIdx)
{
	switch (charsetIdx) {

	case CONV_CHARSET_UNICODE:
		if (m_pUniCharset == NULL)
			m_pUniCharset = new UnicodeCharset(UnicodeTable);
		return m_pUniCharset;
	case CONV_CHARSET_UNIDECOMPOSED:
		if (m_pUniCompCharset == NULL)
			m_pUniCompCharset = new UnicodeCompCharset(UnicodeTable, UnicodeComposite);
		return m_pUniCompCharset;
	case CONV_CHARSET_UNIUTF8:
  case CONV_CHARSET_XUTF8:
		if (m_pUniUTF8 == NULL)
			m_pUniUTF8 = new UnicodeUTF8Charset(UnicodeTable);
		return m_pUniUTF8;

	case CONV_CHARSET_UNIREF:
		if (m_pUniRef == NULL)
			m_pUniRef = new UnicodeRefCharset(UnicodeTable);
		return m_pUniRef;

	case CONV_CHARSET_UNIREF_HEX:
		if (m_pUniHex == NULL)
			m_pUniHex = new UnicodeHexCharset(UnicodeTable);
		return m_pUniHex;

	case CONV_CHARSET_UNI_CSTRING:
		if (m_pUniCString == NULL)
			m_pUniCString = new UnicodeCStringCharset(UnicodeTable);
		return m_pUniCString;

	case CONV_CHARSET_WINCP1258:
		if (m_pWinCP1258 == NULL)
			m_pWinCP1258 = new WinCP1258Charset(WinCP1258, WinCP1258Pre);
		return m_pWinCP1258;

	case CONV_CHARSET_VIQR:
		if (m_pVIQRCharObj == NULL)
			m_pVIQRCharObj = new VIQRCharset(VIQRTable);
		return m_pVIQRCharObj;

	case CONV_CHARSET_VNSTANDARD:
		if (m_pVnIntCharset == NULL)
			m_pVnIntCharset = new VnInternalCharset();
		return m_pVnIntCharset;

	case CONV_CHARSET_UTF8VIQR:
	  if (m_pUVIQRCharObj == NULL) {
	    if (m_pVIQRCharObj == NULL)
	      m_pVIQRCharObj = new VIQRCharset(VIQRTable);

	    if (m_pUniUTF8 == NULL)
	      m_pUniUTF8 = new UnicodeUTF8Charset(UnicodeTable);
	    m_pUVIQRCharObj = new UTF8VIQRCharset(m_pUniUTF8, m_pVIQRCharObj);
	  }
	  return m_pUVIQRCharObj;

	default:
		if (IS_SINGLE_BYTE_CHARSET(charsetIdx)) {
			int i = charsetIdx - CONV_CHARSET_TCVN3;
			if (m_sgCharsets[i] == NULL)
				m_sgCharsets[i] = new SingleByteCharset(SingleByteTables[i]);
			return m_sgCharsets[i];
		}
		else if (IS_DOUBLE_BYTE_CHARSET(charsetIdx)) {
			int i = charsetIdx - CONV_CHARSET_VNIWIN;
			if (m_dbCharsets[i] == NULL)
				m_dbCharsets[i] = new DoubleByteCharset(DoubleByteTables[i]);
			return m_dbCharsets[i];
		}
	}
	return NULL;
}
