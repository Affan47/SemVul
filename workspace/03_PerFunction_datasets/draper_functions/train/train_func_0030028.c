writeRangeAllocateCode(Output& out, const TypePtr& type, const string& fixedName, const StringList& metaData,
                              bool inParam)
{
    if(!inParam)
    {
        return;
    }

    SequencePtr seq = SequencePtr::dynamicCast(type);
    if(seq)
    {
        string seqType = findMetaData(metaData, true);
        if(seqType.find("range") == 0 && seqType != "range:array")
        {
            StringList md;
            if(seqType.find("range:") == 0)
            {
                md.push_back("cpp:type:" + seqType.substr(strlen("range:")));
            }
            out << nl << typeToString(seq, false, md, false) << " ___" << fixedName << ";";
        }
    }
}
