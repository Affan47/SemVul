writeMessages(Buffer &buffer, int offset)
{
    for (MsgMap::iterator i = messages.begin(); i != messages.end(); i++) {
        MsgEntry &e = (*i).second;
        e.offset = offset;
        offset += e.message->save(buffer);
    }
    return offset;
}
