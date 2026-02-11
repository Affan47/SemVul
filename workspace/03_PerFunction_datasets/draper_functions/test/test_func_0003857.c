writeStringSet(const StringSet & ss, Sink & sink)
{
    writeInt(ss.size(), sink);
    for (StringSet::iterator i = ss.begin(); i != ss.end(); ++i)
        writeString(*i, sink);
}
