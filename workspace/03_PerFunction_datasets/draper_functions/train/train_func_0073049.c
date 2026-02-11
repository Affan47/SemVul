xmlnode_localName(const fn_call& fn)
{
    XMLNode_as* ptr = ensure<ThisIsNative<XMLNode_as> >(fn);


    if (ptr->nodeName().empty()) {
        as_value null;
        null.set_null();
        return null;
    }

    const std::string& nodeName = ptr->nodeName();
    if (nodeName.empty()) return as_value("");

    std::string::size_type pos = nodeName.find(':');
    if (pos == std::string::npos || pos == nodeName.size() - 1) {
        return as_value(nodeName);
    }

    return as_value(nodeName.substr(pos + 1));
}
