add(DowntimeOrComment *data)
{
    dc_key tmp_key = make_pair(data->_id, data->_service != 0);
    _entries_t::iterator it = _entries.find(tmp_key);


    if (it != _entries.end()) {
        delete it->second;
        _entries.erase(it);
    }
    _entries.insert(make_pair(tmp_key, data));
}
