print(STD_NAMESPACE ostream &stream,
                                          const size_t flags) const
{
    const char *modality = dcmSOPClassUIDToModality(SOPClassUID.c_str());
    stream << "(";
    if (modality != NULL)
        stream << modality << " image";
    else
        stream << "\"" << SOPClassUID << "\"";
    stream << ",";
    if (flags & DSRTypes::PF_printSOPInstanceUID)
        stream << "\"" << SOPInstanceUID << "\"";
    if (!FrameList.isEmpty())
    {
        stream << ",";
        FrameList.print(stream, flags);
    }
    stream << ")";
    if (PresentationState.isValid())
    {
        stream << ",(GSPS,";
        if (flags & DSRTypes::PF_printSOPInstanceUID)
            stream << "\"" << PresentationState.getSOPInstanceUID() << "\"";
        stream << ")";
    }
    return EC_Normal;
}
