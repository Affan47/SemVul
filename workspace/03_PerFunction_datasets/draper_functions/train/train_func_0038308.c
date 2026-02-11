proc_readyReadStdout()
	{
		if(collectOutput)
		{
			QByteArray a = proc.readStdout();
			if(readText)
				a = readConv.update(a);
			buf_stdout.append(a);
		}
		else
			emit readyRead();
	}
