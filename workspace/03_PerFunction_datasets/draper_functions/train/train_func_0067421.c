renderHTMLContentItem(STD_NAMESPACE ostream &docStream,
                                                    STD_NAMESPACE ostream & ,
                                                    const size_t ,
                                                    size_t & ,
                                                    const size_t flags) const
{

    OFCondition result = renderHTMLConceptName(docStream, flags);

    if (result.good())
    {
        OFString tmpString, htmlString;
        if (!(flags & DSRTypes::HF_renderItemsSeparately))
        {
            if (flags & DSRTypes::HF_XHTML11Compatibility)
                docStream << "<span class=\"pname\">";
            else if (flags & DSRTypes::HF_HTML32Compatibility)
                docStream << "<u>";
            else
                docStream << "<span class=\"under\">";
        }
        docStream << convertToHTMLString(dicomToReadablePersonName(getValue(), tmpString), htmlString, flags);
        if (!(flags & DSRTypes::HF_renderItemsSeparately))
        {
            if (flags & DSRTypes::HF_HTML32Compatibility)
                docStream << "</u>";
            else
                docStream << "</span>";
        }
        docStream << OFendl;
    }
    return result;
}
