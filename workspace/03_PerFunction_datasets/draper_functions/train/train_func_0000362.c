run()
	{
		m_file_mutex.lock();
		do {
			File file = m_files.takeLast();
			m_files.clear();
			m_file_mutex.unlock();

			CacheFile cache_file = { file, QImage() };
			int index = m_cache.indexOf(cache_file);
			if (index != -1) {
				cache_file = m_cache.at(index);
			} else {
				cache_file.image = Theme::renderBackground(file.image_path, file.position, file.color, file.rect.size());
				m_cache.prepend(cache_file);
				while (m_cache.size() > 10) {
					m_cache.removeLast();
				}
			}

			m_image_mutex.lock();
			m_image = cache_file.image;
			m_image_mutex.unlock();

			m_file_mutex.lock();
		} while (!m_files.isEmpty());
		m_file_mutex.unlock();
	}
