get_ptr() {
    static const ret_val null_ret(std::make_pair(static_cast<starling_read*>(NULL),0));
    if (_head==_end) return null_ret;
    const align_id_t read_id(_head->first);
    const seg_id_t seg_id(_head->second);
    const starling_read_buffer::read_data_t::iterator i(_buff._read_data.find(read_id));
    if (i==_buff._read_data.end()) return null_ret;
    return std::make_pair(i->second,seg_id);
}
