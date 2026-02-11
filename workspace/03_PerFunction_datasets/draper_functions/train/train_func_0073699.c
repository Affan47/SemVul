renderHTML(STD_NAMESPACE ostream &stream,
                                           const size_t flags,
                                           const OFBool fullCode,
                                           const OFBool valueFirst) const
{
    OFString htmlString;
    if (flags & DSRTypes::HF_useCodeDetailsTooltip)
    {

        stream << "<span title=\"(";
        stream << DSRTypes::convertToHTMLString(CodeValue, htmlString, flags) << ", ";
        stream << DSRTypes::convertToHTMLString(CodingSchemeDesignator, htmlString, flags);
        if (!CodingSchemeVersion.empty())
            stream << " [" << DSRTypes::convertToHTMLString(CodingSchemeVersion, htmlString, flags) << "]";
        stream << ", &quot;" << DSRTypes::convertToHTMLString(CodeMeaning, htmlString, flags) << "&quot;)\">";

        if (valueFirst)
            stream << DSRTypes::convertToHTMLString(CodeValue, htmlString, flags);
        else
            stream << DSRTypes::convertToHTMLString(CodeMeaning, htmlString, flags);
        stream << "</span>";
    } else {

        if (valueFirst)
            stream << DSRTypes::convertToHTMLString(CodeValue, htmlString, flags);
        else
            stream << DSRTypes::convertToHTMLString(CodeMeaning, htmlString, flags);
        if (fullCode)
        {
            stream << " (";
            if (!valueFirst)
                stream << DSRTypes::convertToHTMLString(CodeValue, htmlString, flags) << ", ";
            stream << DSRTypes::convertToHTMLString(CodingSchemeDesignator, htmlString, flags);
            if (!CodingSchemeVersion.empty())
                stream << " [" << DSRTypes::convertToHTMLString(CodingSchemeVersion, htmlString, flags) << "]";
            if (valueFirst)
                stream << ", &quot;" << DSRTypes::convertToHTMLString(CodeMeaning, htmlString, flags) << "&quot;";
            stream << ")";
        }
    }
    return EC_Normal;
}
