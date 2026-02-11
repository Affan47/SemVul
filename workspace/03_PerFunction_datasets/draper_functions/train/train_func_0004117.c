ReadFile(const char *path, char *buf, size_t size, off_t offset)
	{
		size_t len = m_error_log.size();
		if( offset >= 0 && offset < (off_t)len ) {
			if( (offset + size) > len )
				size = len - offset;
			memcpy(buf, m_error_log.data() + offset, size);
		}
		else {
			size = 0;
		}
		return size;
	}
