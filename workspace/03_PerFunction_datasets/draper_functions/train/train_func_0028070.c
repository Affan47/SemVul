ManageReceivedPacket(unsigned char *buffer, unsigned short readSize, const Nc::Network::Ip &ip, unsigned short port)
{

    Sender *sender = NULL;
    for (ListSender::iterator it = _clients.begin(); sender == NULL && it != _clients.end(); ++it)
        if(it->ip == ip && it->port == port)
            sender = &(*it);
    if (sender != NULL)
    {
        unsigned int headerSize = sender->instance->UdpLayer().HeaderSize();
        if (readSize < headerSize)
        {
            Error(UNKNOWN_PACKET);
            return readSize;
        }


        unsigned short  sequence = 0;
        if (sender->instance->UdpLayer().ParseHeader(buffer, readSize, sequence))
        {
            unsigned int pos = headerSize;
            while (pos <= (readSize - sizeof(ReliableLayer::DataHeader)))
            {
                ReliableLayer::DataHeader   *dataHeader = (ReliableLayer::DataHeader*)(buffer + pos);
                unsigned char               *packet = buffer + pos + sizeof(ReliableLayer::DataHeader);

                pos += sizeof(ReliableLayer::DataHeader);
                pos += dataHeader->size;
                if (pos > readSize)
                    Error(CORRUPTED_PACKET);
                else
                {

                    MapCallbackMethod::iterator it = sender->methods.find(dataHeader->code);
                    if (it != sender->methods.end())
                    {
                        if (!it->second.mostRecentOnly || it->second.currentSequence == -1 || PacketQueue::SequenceMoreRecent(sequence, it->second.currentSequence))
                        {
                            it->second.currentSequence = sequence;
                            sender->instance->CallCallback(it->second.method, Packet(packet, dataHeader->size));
                        }
                        else
                            LOG_DEBUG << "Droping packet." << std::endl;
                    }
                    else
                        Error(UNKNOWN_PACKET);
                }
            }
        }
    }
    else
        Error(UNKNOWN_SENDER);
    return readSize;
}
