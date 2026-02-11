getContent(const OpticalDisc::Identity &info,
                                                const QByteArray &file)
    {
        if (!m_pointer) {
            return advancedDiscDetect(file);
        }

        if (!m_semaphore.acquire()) {
            return advancedDiscDetect(file);
        }
        Releaser releaser(&m_semaphore);

        if (!m_shmem.lock()) {
            return advancedDiscDetect(file);
        }
        Unlocker unlocker(&m_shmem);

        if (!m_pointer->find(info)) {
            m_pointer->add(info, advancedDiscDetect(file));
        }

        Solid::OpticalDisc::ContentTypes content = m_pointer->front().second;
        return content;
    }
