RecvDatagram (SOCKET socket) {
    Datagram data(socket);
    data.Recv();
    const Address& addr = data.address();
#define return_log(...) { fprintf(stderr,__VA_ARGS__); return; }
    if (data.size()<4)
        return_log("datagram shorter than 4 bytes %s\n",addr.str());
    uint32_t mych = data.Pull32();
    Sha1Hash hash;
    Channel* channel = NULL;
    if (!mych) {
        if (data.size()<1+4+1+4+Sha1Hash::SIZE)
            return_log ("%s #0 incorrect size %i initial handshake packet %s\n",
                        tintstr(),data.size(),addr.str());
        uint8_t hashid = data.Pull8();
        if (hashid!=SWIFT_HASH)
            return_log ("%s #0 no hash in the initial handshake %s\n",
                        tintstr(),addr.str());
        bin64_t pos = data.Pull32();
        if (pos!=bin64_t::ALL)
            return_log ("%s #0 that is not the root hash %s\n",tintstr(),addr.str());
        hash = data.PullHash();
        FileTransfer* file = FileTransfer::Find(hash);
        if (!file)
            return_log ("%s #0 hash %s unknown, no such file %s\n",tintstr(),hash.hex().c_str(),addr.str());
        dprintf("%s #0 -hash ALL %s\n",tintstr(),hash.hex().c_str());
        for(binqueue::iterator i=file->hs_in_.begin(); i!=file->hs_in_.end(); i++)
            if (channels[*i] && channels[*i]->peer_==data.address() &&
                channels[*i]->last_recv_time_>NOW-TINT_SEC*2)
                return_log("%s #0 have a channel already to %s\n",tintstr(),addr.str());
        channel = new Channel(file, socket, data.address());
    } else {
        mych = DecodeID(mych);
        if (mych>=channels.size())
            return_log("%s invalid channel #%u, %s\n",tintstr(),mych,addr.str());
        channel = channels[mych];
        if (!channel)
            return_log ("%s #%u is already closed\n",tintstr(),mych,addr.str());
        if (channel->peer() != addr)
            return_log ("%s #%u invalid peer address %s!=%s\n",
                        tintstr(),mych,channel->peer().str(),addr.str());
        channel->own_id_mentioned_ = true;
    }

    channel->Recv(data);
}
