update(const MemoryRegion &m)
{
	QByteArray a = m.toByteArray();
	if(_dir == Encode)
	{
		QByteArray out(a.size() * 2, 0);
		int at = 0;
		int c;
		for(int n = 0; n < (int)a.size(); ++n)
		{
			uchar lo = (uchar)a[n] & 0x0f;
			uchar hi = (uchar)a[n] >> 4;
			c = enhex(hi);
			if(c == -1)
			{
				_ok = false;
				break;
			}
			out[at++] = (char)c;
			c = enhex(lo);
			if(c == -1)
			{
				_ok = false;
				break;
			}
			out[at++] = (char)c;
		}
		if(!_ok)
			return MemoryRegion();

		return out;
	}
	else
	{
		uchar lo = 0;
		uchar hi = 0;
		bool flag = false;
		if(partial)
		{
			hi = val;
			flag = true;
		}

		QByteArray out(a.size() / 2, 0);
		int at = 0;
		int c;
		for(int n = 0; n < (int)a.size(); ++n)
		{
			c = dehex((char)a[n]);
			if(c == -1)
			{
				_ok = false;
				break;
			}
			if(flag)
			{
				lo = (uchar)c;
				uchar full = ((hi & 0x0f) << 4) + (lo & 0x0f);
				out[at++] = full;
				flag = false;
			}
			else
			{
				hi = (uchar)c;
				flag = true;
			}
		}
		if(!_ok)
			return MemoryRegion();

		if(flag)
		{
			val = hi;
			partial = true;
		}
		return out;
	}
}
