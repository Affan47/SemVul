encodeMsgHeader(AMF_msg::message_header_t *head)
{


    boost::shared_ptr<cygnal::Buffer> buf (new cygnal::Buffer(sizeof(AMF_msg::message_header_t)));


    boost::uint16_t length = head->target.size();
    *buf = length;
    *buf += head->target;


    length = head->response.size();
    *buf += length;
    *buf += head->target;


    *buf += static_cast<boost::uint32_t>(head->size);

    return buf;
}
