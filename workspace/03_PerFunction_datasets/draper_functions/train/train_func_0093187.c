set_reserved( const string& s)
{
        LOG_ERROR ("You just voided your warranty: Writing this to \"reserved\" field in EDF header: %s", s.c_str());
        _recording_id = s;
        memcpy( header.reserved, pad( s, 44).c_str(), 44);
        return s.size() > 44;
}
