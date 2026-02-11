pop_front()
{
    uint8_t x = m_read_buf[m_ridx];
    ++m_ridx;
    if (m_ridx ==  m_buffer_size) {
        if (m_disk_buffered_blocks > 0) {
            m_stream.seekg(m_buffer_size * (m_rb++), std::ios::beg);
            m_stream.read((char*) m_read_buf, m_buffer_size);
            --m_disk_buffered_blocks;
        } else {
            m_sync = 1;
            memcpy(m_read_buf, m_write_buf, m_widx+1);
        }
        m_ridx = 0;
    }
    return x;
}
