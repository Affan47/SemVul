print(STD_NAMESPACE ostream& stream, E_Representation representation) const
{
    switch (representation) {
    case ER_RepresentationOID:
        stream << "2.25.";

    case ER_RepresentationInteger:
        printInteger(stream);
        break;
    case ER_RepresentationURN:
        stream << "urn:uuid:";

    case ER_RepresentationHex:
        printHex(stream);
        break;
    }

    return stream;
}
