OnData (Datagram& dgram) {
    bin64_t pos = dgram.Pull32();
    uint8_t *data;
    int length = dgram.Pull(&data,1024);
    bool ok = (pos==bin64_t::NONE) || file().OfferData(pos, (char*)data, length) ;
    dprintf("%s #%u %cdata %s\n",tintstr(),id_,ok?'-':'!',pos.str());
    data_in_ = tintbin(NOW,bin64_t::NONE);
    if (!ok)
        return bin64_t::NONE;
    data_in_.bin = pos;
    if (pos!=bin64_t::NONE) {
        if (last_data_in_time_) {
            tint dip = NOW - last_data_in_time_;
            dip_avg_ = ( dip_avg_*3 + dip ) >> 2;
        }
        last_data_in_time_ = NOW;
    }
    CleanHintOut(pos);
    return pos;
}
