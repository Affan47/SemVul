prep_in_buffer()
{
    m_in_buf_left = 0;
    m_pIn_buf_ofs = m_in_buf;

    if (m_eof_flag) {
        return;
    }

    do {
        int bytes_read = m_pStream->read(m_in_buf + m_in_buf_left, JPGD_IN_BUF_SIZE - m_in_buf_left, &m_eof_flag);
        if (bytes_read == -1) {
            stop_decoding(JPGD_STREAM_READ);
        }

        m_in_buf_left += bytes_read;
    } while ((m_in_buf_left < JPGD_IN_BUF_SIZE) && (!m_eof_flag));

    m_total_bytes_read += m_in_buf_left;


    word_clear(m_pIn_buf_ofs + m_in_buf_left, 0xD9FF, 64);
}
