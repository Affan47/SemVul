determineRepresentation(const DiDocument *docu)
{
    UsedBits = DicomImageClass::rangeToBits(MinValue, MaxValue);
    if ((docu != NULL) && (docu->getFlags() & CIF_UseAbsolutePixelRange))
        Representation = DicomImageClass::determineRepresentation(AbsMinimum, AbsMaximum);
    else
        Representation = DicomImageClass::determineRepresentation(MinValue, MaxValue);
    DCMIMGLE_TRACE("internal representation for monochrome images: "
        << DicomImageClass::getRepresentationBits(Representation) << " bits ("
        << (DicomImageClass::isRepresentationSigned(Representation) ? "signed" : "unsigned") << ")");
}
