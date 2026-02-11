TimeoutDataOut ( ) {

    tint timeout = NOW - ack_timeout();
    while (!data_out_.empty() &&
        ( data_out_.front().time<timeout || data_out_.front()==tintbin() ) ) {
        if (data_out_.front()!=tintbin() && ack_in_.is_empty(data_out_.front().bin)) {
            ack_not_rcvd_recent_++;
            data_out_cap_ = bin64_t::ALL;
            data_out_tmo_.push_back(data_out_.front().bin);
            dprintf("%s #%u Tdata %s\n",tintstr(),id_,data_out_.front().bin.str());
        }
        data_out_.pop_front();
    }

    while (!data_out_tmo_.empty() && data_out_tmo_.front().time<NOW-MAX_POSSIBLE_RTT)
        data_out_tmo_.pop_front();
}
