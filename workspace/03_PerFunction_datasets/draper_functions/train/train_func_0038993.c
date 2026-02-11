AddLevel(const Level* level) {
    if(level == NULL)
        return false;
    std::ostringstream stream;
    if(!level->Save_SubMSCC(stream, false))
        return false;
    if(stream.str().size() > 65535)
        return false;
    msccdata.push_back(stream.str());
    return true;
}
