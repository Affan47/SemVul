HandleSessionCallback(SoupSession *session,
                                               SoupMessage *msg)
{

    m_responseContentType = "";
    if (msg->response_body) {
        m_response = soup_message_body_flatten(msg->response_body);
        const char *soupContentType = soup_message_headers_get(msg->response_headers,
                                                               "Content-Type");
        if (soupContentType) {
            m_responseContentType = soupContentType;
        }
    } else {
        m_response = NULL;
    }
    if (msg->status_code != 200) {
        m_failure = m_URL;
        m_failure += " via libsoup: ";
        m_failure += msg->reason_phrase ? msg->reason_phrase : "failed";
        m_status = FAILED;

        if (m_responseContentType.find("text") != std::string::npos) {
            SE_LOG_DEBUG(NULL, "unexpected HTTP response: status %d/%s, content type %s, body:\n%.*s",
                         msg->status_code, msg->reason_phrase ? msg->reason_phrase : "<no reason>",
                         m_responseContentType.c_str(),
                         m_response ? (int)m_response->length : 0,
                         m_response ? m_response->data : "");
        }
    } else {
        m_status = GOT_REPLY;
    }

    g_main_loop_quit(m_loop.get());
}
