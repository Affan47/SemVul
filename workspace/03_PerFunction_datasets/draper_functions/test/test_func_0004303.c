update(const QByteArray &buf)
	{
		if(mode == Read)
		{
			QByteArray out;

			if(state == Normal)
			{
				out = buf;
			}
			else
			{
				out.resize(buf.size() + 1);
				out[0] = '\r';
				memcpy(out.data() + 1, buf.data(), buf.size());
			}

			int n = 0;
			while(1)
			{
				n = out.indexOf('\r', n);

				if(n == -1)
				{
					break;
				}

				if(n < (buf.size() - 1))
				{
					if(out[n + 1] == '\n')
					{

						memmove(out.data() + n, out.data() + n + 1, out.size() - n - 1);
						out.resize(out.size() - 1);
					}
				}

				else
				{
					state = Partial;
					break;
				}
				++n;
			}

			return out;
		}
		else
		{
			if(write_conv)
			{
				QByteArray out;
				int prev = 0;
				int at = 0;

				while(1)
				{
					int n = buf.indexOf('\n', at);
					if(n == -1)
						break;

					int chunksize = n - at;
					int oldsize = out.size();
					out.resize(oldsize + chunksize + 2);
					memcpy(out.data() + oldsize, buf.data() + at, chunksize);
					memcpy(out.data() + oldsize + chunksize, "\r\n", 2);

					list.append(prebytes + n + 1 - prev);
					prebytes = 0;
					prev = n;

					at = n + 1;
				}
				if(at < buf.size())
				{
					int chunksize = buf.size() - at;
					int oldsize = out.size();
					out.resize(oldsize + chunksize);
					memcpy(out.data() + oldsize, buf.data() + at, chunksize);
				}

				prebytes += buf.size() - prev;
				return out;
			}
			else
				return buf;
		}
	}
