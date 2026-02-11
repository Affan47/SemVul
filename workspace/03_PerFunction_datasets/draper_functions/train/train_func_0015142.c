bs_readyRead()
	{
		QByteArray buf = bs->readAll();

		if(tls)
			tls->writeIncoming(buf);
		else
			processStream(buf);
	}
