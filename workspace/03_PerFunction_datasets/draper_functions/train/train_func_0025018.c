getReply(const char *&data, size_t &len, std::string &contentType)
{
    if (m_response) {
        data = m_response->data;
        len = m_response->length;
        contentType = m_responseContentType;
    } else {
        data = NULL;
        len = 0;
    }
}
