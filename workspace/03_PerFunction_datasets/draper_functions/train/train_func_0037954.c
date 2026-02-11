push_back(uint8_t x)
{
    m_write_buf[m_widx] = x;
    if (m_sync) {
        m_read_buf[m_widx] = x;
    }
    ++m_widx;
    if (m_widx == m_buffer_size) {
        if (!m_sync) {
            if (!m_stream.is_open()) {
                m_stream.open(m_file_name.c_str(), std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
            }
            m_stream.seekp(m_buffer_size * (m_wb++), std::ios::beg);

            m_stream.write((char*) m_write_buf, m_buffer_size);

            ++m_disk_buffered_blocks;
        }
        m_sync = 0;
        m_widx = 0;
    }
}
