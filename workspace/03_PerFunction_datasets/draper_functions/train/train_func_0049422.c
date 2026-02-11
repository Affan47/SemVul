seek(long value, int whence) {
		if(lseek(f, value, whence)<0)
			throw Exception(IMAGE_FORMAT,
				&file_name,
				"seek(value=%ld, whence=%d) failed: %s (%d), actual filename '%s'",
					value, whence, strerror(errno), errno, fname);
	}
