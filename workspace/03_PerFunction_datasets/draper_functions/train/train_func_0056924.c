writeData(const char *data, qint64 len)
        {
            if (len) {

                const QByteArray buf(data, len);
                syslog(m_priority, "%s", buf.constData());
            }
            return len;
        }
