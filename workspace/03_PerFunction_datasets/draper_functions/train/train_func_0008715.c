final()
	{
		if(secure)
		{
			SecureArray b(16, 0);
			md5_finish(&md5, (md5_byte_t *)b.data());
			return b;
		}
		else
		{
			QByteArray b(16, 0);
			md5_finish(&md5, (md5_byte_t *)b.data());
			return b;
		}
	}
