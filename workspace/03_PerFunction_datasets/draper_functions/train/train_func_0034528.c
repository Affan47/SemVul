xmlnode_new(const fn_call& fn)
{

    as_object* obj = ensure<ValidThis>(fn);

    if (!fn.nargs) {
        return as_value();
    }

    std::auto_ptr<XMLNode_as> xml(new XMLNode_as(getGlobal(fn)));
    xml->nodeTypeSet(XMLNode_as::NodeType(toInt(fn.arg(0), getVM(fn))));

    if (fn.nargs > 1) {
        const std::string& str = fn.arg(1).to_string();
        switch (xml->nodeType())
        {
            case XMLNode_as::Element:
                xml->nodeNameSet(str);
                break;
            default:
                xml->nodeValueSet(str);
                break;
        }
    }


    xml->setObject(obj);
    obj->setRelay(xml.release());

    return as_value();
}
