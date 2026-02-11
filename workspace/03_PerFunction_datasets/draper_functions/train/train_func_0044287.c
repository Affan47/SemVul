Entry()
{
	if (m_file->GetFileSize() == 0) {
		m_result = 0;
		return;
	}

	uint64_t minFree = thePrefs::IsCheckDiskspaceEnabled() ? thePrefs::GetMinFreeDiskSpace() : 0;
	int64_t freeSpace = CPath::GetFreeSpaceAt(thePrefs::GetTempDir());


	if (freeSpace != wxInvalidOffset) {
		if ((uint64_t)freeSpace < m_file->GetFileSize() + minFree) {
			m_result = ENOSPC;
			return;
		}
	}

	CFile file;
	file.Open(m_file->GetFullName().RemoveExt(), CFile::read_write);

#ifdef __WXMSW__
	try {


		file.Seek(m_file->GetFileSize() - 1, wxFromStart);
		file.WriteUInt8(0);
		file.Close();
		m_result = 0;
	} catch (const CSafeIOException&) {
		m_result = errno;
	}
#else

#  ifdef HAVE_FALLOCATE
	m_result = fallocate(file.fd(), 0, 0, m_file->GetFileSize());
#  elif defined HAVE_SYS_FALLOCATE
	m_result = syscall(SYS_fallocate, file.fd(), 0, (loff_t)0, (loff_t)m_file->GetFileSize());
	if (m_result == -1) {
		m_result = errno;
	}
#  elif defined HAVE_POSIX_FALLOCATE

	m_result = posix_fallocate(file.fd(), 0, m_file->GetFileSize());
#  endif

	if (m_result != 0 && m_result != ENOSPC) {

#  define BLOCK_SIZE	1048576
		void *zero = calloc(1, BLOCK_SIZE);
		if (zero != NULL) {
			try {
				uint64_t size = m_file->GetFileSize();
				for (; size >= BLOCK_SIZE; size -= BLOCK_SIZE) {
					file.Write(zero, BLOCK_SIZE);
				}
				if (size > 0) {
					file.Write(zero, size);
				}
				file.Close();
				m_result = 0;
			} catch (const CSafeIOException&) {
				m_result = errno;
			}
			free(zero);
		} else {
			m_result = ENOMEM;
		}
	}

#endif
	if (file.IsOpened()) {
		file.Close();
	}
}
