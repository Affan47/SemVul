convertToUtf8()
	{

		QTextCodec *codec = QTextCodec::codecForMib(106);
		QTextCodec::ConverterState cstate(QTextCodec::IgnoreHeader);
		SecureArray out;
		ushort *ustr = (ushort *)result.data();
		int len = result.size() / sizeof(ushort);
		for(int n = 0; n < len; ++n)
		{
			QChar c(ustr[n]);
			out += codec->fromUnicode(&c, 1, &cstate);
		}
		result = out;
	}
