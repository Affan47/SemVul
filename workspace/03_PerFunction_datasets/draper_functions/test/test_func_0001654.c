printInfoLineStart(STD_NAMESPACE ostream &out,
                                   const size_t flags,
                                   const int level,
                                   DcmTag *tag)
{

    if (tag == NULL)
        tag = &Tag;
    DcmVR vr(tag->getVR());

    printNestingLevel(out, flags, level);
    if (flags & DCMTypes::PF_showTreeStructure)
    {
        if (flags & DCMTypes::PF_useANSIEscapeCodes)
        {
            if (*tag == DCM_Item)
                out << DCMDATA_ANSI_ESCAPE_CODE_ITEM;
            else if ((vr.getEVR() == EVR_SQ) || (vr.getEVR() == EVR_pixelSQ))
            {
                if (level == 1)
                    out << DCMDATA_ANSI_ESCAPE_CODE_SEQUENCE_1;
                else
                    out << DCMDATA_ANSI_ESCAPE_CODE_SEQUENCE;
            } else if (level == 1)
                out << DCMDATA_ANSI_ESCAPE_CODE_NAME_1;
            else
                out << DCMDATA_ANSI_ESCAPE_CODE_NAME;
        }

        out << tag->getTagName() << ' ';

        const STD_NAMESPACE ptrdiff_t padLength = DCM_OptPrintAttributeNameLength - strlen(tag->getTagName()) - 2 * level;
        if (padLength > 0)
            out << OFString(OFstatic_cast(size_t, padLength), ' ');
    } else {
        if (flags & DCMTypes::PF_useANSIEscapeCodes)
            out << DCMDATA_ANSI_ESCAPE_CODE_TAG;

        out << *tag << " ";
        if (flags & DCMTypes::PF_useANSIEscapeCodes)
            out << DCMDATA_ANSI_ESCAPE_CODE_VR;

        out << vr.getVRName() << " "
            << STD_NAMESPACE dec << STD_NAMESPACE setfill(' ');
    }

    if (flags & DCMTypes::PF_useANSIEscapeCodes)
        out << DCMDATA_ANSI_ESCAPE_CODE_VALUE;
}
