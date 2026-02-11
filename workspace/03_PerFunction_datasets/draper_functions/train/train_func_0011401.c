writeXMLEndTag(STD_NAMESPACE ostream &out,
                                const size_t flags)
{

    if (flags & DCMTypes::XF_useNativeModel)
        out << "</DicomAttribute>" << OFendl;
    else
        out << "</element>" << OFendl;
}
