processStatusData(const QByteArray &buf)
	{
		statusBuf.append(buf);


		QStringList list;
		while(1)
		{
			int n = statusBuf.indexOf('\n');
			if(n == -1)
				break;


			++n;
			char *p = (char *)statusBuf.data();
			QByteArray cs(p, n);
			int newsize = statusBuf.size() - n;
			memmove(p, p + n, newsize);
			statusBuf.resize(newsize);


			QString str = QString::fromUtf8(cs);
			str.truncate(str.length() - 1);


			if(str.left(9) != "[GNUPG:] ")
				continue;


			str = str.mid(9);


			list += str;
		}

		if(list.isEmpty())
			return false;

		statusLines += list;
		return true;
	}
