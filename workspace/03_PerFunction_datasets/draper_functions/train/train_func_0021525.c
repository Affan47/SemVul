print(STD_NAMESPACE ostream &stream,
                                              const size_t ) const
{
    if (isEmpty())
    {

        stream << "empty";
    } else {
        OFString printString;
        stream << "\"" << DSRTypes::convertToPrintString(NumericValue, printString) << "\" ";
        MeasurementUnit.print(stream, OFTrue , OFTrue );
    }
    return EC_Normal;
}
