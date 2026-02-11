getXmlBoolAttribute(TiXmlElement *xmlElement, string attrName, bool defaultValue) {
    if (xmlElement == NULL) {
        return defaultValue;
    }
    const char * boolStringValue = xmlElement->Attribute(attrName.c_str());

    if (boolStringValue != NULL) {
        string trueFalseStr = boolStringValue;
        transform(trueFalseStr.begin(), trueFalseStr.end(), trueFalseStr.begin(), ::tolower );
        if ((trueFalseStr == "yes") || (trueFalseStr == "true") || (trueFalseStr == "1")) {
            return true;
        } else if ((trueFalseStr == "no") || (trueFalseStr == "false") || (trueFalseStr == "0")) {
            return false;
        } else {
            return defaultValue;
        }
    } else {
        return defaultValue;
    }
}
