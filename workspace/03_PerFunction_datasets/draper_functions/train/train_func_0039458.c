parseAMFPacket(boost::uint8_t *data, size_t size)
{
    GNASH_REPORT_FUNCTION;

    boost::uint8_t *ptr = data + sizeof(AMF_msg::context_header_t);
    boost::shared_ptr<context_header_t> header = AMF_msg::parseContextHeader(data, size);


    AMF amf;

    try {
        for (int i=0; i<header->messages; i++) {
            boost::shared_ptr<AMF_msg::amf_message_t> msgpkt(new AMF_msg::amf_message_t);
            boost::shared_ptr<AMF_msg::message_header_t> msghead = AMF_msg::parseMessageHeader(ptr, size);
            if (msghead) {
                ptr += msghead->target.size() + msghead->response.size()
                    + (sizeof(boost::uint16_t) * 2)
                    + (sizeof(boost::uint32_t));
                boost::shared_ptr<cygnal::Element> el = amf.extractAMF(ptr, ptr+size);
                msgpkt->header.target = msghead->target;
                msgpkt->header.response = msghead->response;
                msgpkt->header.size = msghead->size;
                msgpkt->data = el;
                ptr += amf.totalsize();

                _messages.push_back(msgpkt);
            }
        }
    } catch(std::exception& e) {
        log_error(_("Error parsing the AMF packet: \n\t%s"), e.what());
    }

    return header;
}
