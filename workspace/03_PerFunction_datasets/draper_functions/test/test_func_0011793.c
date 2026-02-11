parseShortHand(int propId, const int *properties, const int numProperties, bool important)
{
    if (valueList->size() > numProperties) {

        return false;
    }

    ShorthandScope scope(this, propId);


    const int oldNumParsedProperties = numParsedProperties;


    bool fnd[6];
    for( int i = 0; i < numProperties; i++ )
        fnd[i] = false;

    bool discard = false;
    unsigned short numValidProperties = 0;
    bool foundValid = false;
    while ( valueList->current() ) {
        foundValid = false;
        for (int propIndex = 0; propIndex < numProperties; ++propIndex) {
            if (parseValue(properties[propIndex], important)) {
                foundValid = true;
                ++numValidProperties;
                if (fnd[propIndex]) {
                    discard = true;
                } else {
                    fnd[propIndex] = true;
                }

                break;
            }
        }


        if (!foundValid) {
            discard = true;
        }

        if (discard) {
            break;
        }
    }

    if (discard) {

        rollbackParsedProperties(oldNumParsedProperties);
        return false;
    }

    if (numValidProperties == numProperties) {
        return true;
    }


    m_implicitShorthand = true;
    for (int i = 0; i < numProperties; ++i) {
        if (!fnd[i])
            addProperty(properties[i], new CSSInitialValueImpl(true), important);
    }
    m_implicitShorthand = false;

    return true;
}
