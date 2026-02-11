receive (bool block)
{
    LOG4CPLUS_TRACE(logger, "[encmq::node::receive] ENTER (unknown)");
    LOG4CPLUS_TRACE(logger, "[encmq::node::receive] block = " << block);


    message::envelope envelope;


    zmq_msg_t message;
    zmq_msg_init(&message);

    if (zmq_recvmsg(m_socket, &message, (block ? 0 : ZMQ_DONTWAIT)) == ZMQ_ERROR)
    {
        if (errno == EAGAIN)
        {
            zmq_msg_close(&message);
            LOG4CPLUS_TRACE(logger, "[encmq::node::receive] EXIT = NULL");
            return NULL;
        }
        else
        {
            zmq_msg_close(&message);
            LOG4CPLUS_ERROR(logger, "[encmq::node::receive] zmq_recvmsg = " << zmq_strerror(errno));
            throw exception(ENCMQ_ERROR_UNKNOWN);
        }
    }


    unserialize(&message, &envelope);
    zmq_msg_close(&message);


    if (!after_receive(&envelope))
    {
        LOG4CPLUS_WARN(logger, "[encmq::node::receive] Custom processing error.");
        throw exception(ENCMQ_ERROR_UNKNOWN);
    }


    string str((char *) envelope.msg_data().c_str(), envelope.msg_size());


    if (!decrypt((unsigned char *) str.c_str(), str.size()))
    {
        LOG4CPLUS_WARN(logger, "[encmq::node::receive] Decryption error.");
        throw exception(ENCMQ_ERROR_SSL_AES);
    }


    if (generate_mac(str) != envelope.mac())
    {
        LOG4CPLUS_WARN(logger, "[encmq::node::receive] Unverified MAC.");
        throw exception(ENCMQ_ERROR_WRONG_MAC);
    }


    const Descriptor * desc = DescriptorPool::generated_pool()->FindMessageTypeByName(envelope.msg_type());

    if (desc == NULL)
    {
        LOG4CPLUS_WARN(logger,  "[encmq::node::receive] Message type cannot be found by specified name.");
        LOG4CPLUS_TRACE(logger, "[encmq::node::receive] EXIT = NULL");
        return NULL;
    }


    Message * msg = (MessageFactory::generated_factory()->GetPrototype(desc))->New();
    msg->ParseFromString(str);

    LOG4CPLUS_TRACE(logger, "[encmq::node::receive] EXIT = " << envelope.msg_type());
    return msg;
}
