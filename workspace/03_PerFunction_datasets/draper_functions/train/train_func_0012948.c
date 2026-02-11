addMissingAttributes(TiXmlElement * in, TiXmlElement * out) {
    if ((in==NULL) || (out==NULL)) { return; }
    TiXmlAttribute* pAttrib=in->FirstAttribute();
    while (pAttrib) {
        const char * a  = out->Attribute(pAttrib->Name());
        if (a==NULL) {

            out->SetAttribute(pAttrib->Name(),pAttrib->Value());
        }
        pAttrib=pAttrib->Next();
    }
}
