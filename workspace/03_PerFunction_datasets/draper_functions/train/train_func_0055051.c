print(STD_NAMESPACE ostream&out,
                                   const size_t flags,
                                   const int level,
                                   const char * ,
                                   size_t * )
{
    if (valueLoaded())
    {

        Float32 *floatVals;
        errorFlag = getFloat32Array(floatVals);
        if (floatVals != NULL)
        {
            const unsigned long count = getLengthField() / sizeof(Float32) ;
            const unsigned long maxLength = (flags & DCMTypes::PF_shortenLongTagValues) ?
                DCM_OptPrintLineLength : OFstatic_cast(unsigned long, -1);
            unsigned long printedLength = 0;
            unsigned long newLength = 0;
            char buffer[64];

            printInfoLineStart(out, flags, level);

            for (unsigned int i = 0; i < count; i++, floatVals++)
            {

                if (i == 0)
                    OFStandard::ftoa(buffer, sizeof(buffer), *floatVals, 0, 0, 8 );
                else
                {
                    buffer[0] = '\\';
                    OFStandard::ftoa(buffer + 1, sizeof(buffer) - 1, *floatVals, 0, 0, 8 );
                }

                newLength = printedLength + strlen(buffer);
                if ((newLength <= maxLength) && ((i + 1 == count) || (newLength + 3 <= maxLength)))
                {
                    out << buffer;
                    printedLength = newLength;
                } else {

                    if (i + 1 < count)
                    {
                        out << "...";
                        printedLength += 3;
                    }
                    break;
                }
            }

            printInfoLineEnd(out, flags, printedLength);
        } else
            printInfoLine(out, flags, level, "(no value available)" );
    } else
        printInfoLine(out, flags, level, "(not loaded)" );
}
