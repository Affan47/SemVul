OnPexIn (const Address& addr) {
    for(int i=0; i<hs_in_.size(); i++) {
        Channel* c = Channel::channel(hs_in_[i].toUInt());
        if (c && c->transfer().fd()==this->fd() && c->peer()==addr)
            return;
    }
    if (hs_in_.size()<20) {
        new Channel(this,Channel::default_socket(),addr);
    } else {
        pex_in_.push_back(addr);
        if (pex_in_.size()>1000)
            pex_in_.pop_front();
    }
}
