setFromKeyValue(std::string& key, std::string& value)
{
    std::stringstream parser(value);
    if(key == IDFIELD)
        parser >> m_id;
    else if(key == LENFIELD)
        parser >> m_length;
    else if(key == COVFIELD)
        parser >> m_coverage;
    else if(key == SEQFIELD)
        parser >> m_seq;
    else if(key == ANTFIELD)
        parser >> m_annotation;
    else if(key == UNQFIELD)
    {
        int v;
        parser >> v;
        m_uniqueFlag = (UniqueFlag)v;
    }
    else
        assert(false && "Unknown token found while parsing contig");
}
