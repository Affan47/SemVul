parse4Values(int propId, const int *properties,  bool important )
{


    const int num = inShorthand() ? 1 : valueList->size();


    ShorthandScope scope(this, propId);

    const int oldNumParsedProperties = numParsedProperties;

    switch (num) {
        case 1: {
            if (!parseValue(properties[0], important))
                return false;
            CSSValueImpl *value = parsedProperties[numParsedProperties-1]->value();
            m_implicitShorthand = true;
            addProperty(properties[1], value, important);
            addProperty(properties[2], value, important);
            addProperty(properties[3], value, important);
            m_implicitShorthand = false;
            break;
        }
        case 2: {
            if (!parseValue(properties[0], important) || !parseValue(properties[1], important)) {
                rollbackParsedProperties(oldNumParsedProperties);
                return false;
                }
            CSSValueImpl *value = parsedProperties[numParsedProperties-2]->value();
            m_implicitShorthand = true;
            addProperty(properties[2], value, important);
            value = parsedProperties[numParsedProperties-2]->value();
            addProperty(properties[3], value, important);
            m_implicitShorthand = false;
            break;
        }
        case 3: {
            if (!parseValue(properties[0], important) || !parseValue(properties[1], important) || !parseValue(properties[2], important)) {
                rollbackParsedProperties(oldNumParsedProperties);
                return false;
            }
            CSSValueImpl *value = parsedProperties[numParsedProperties-2]->value();
            m_implicitShorthand = true;
            addProperty(properties[3], value, important);
            m_implicitShorthand = false;
            break;
        }
        case 4: {
            if (!parseValue(properties[0], important) || !parseValue(properties[1], important) ||
                !parseValue(properties[2], important) || !parseValue(properties[3], important)) {
                rollbackParsedProperties(oldNumParsedProperties);
                return false;
            }
            break;
        }
        default: {
            return false;
        }
    }

    return true;
}
