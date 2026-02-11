getNamespaceForPrefix(const std::string& prefix, std::string& ns)
    const
{
    const XMLNode_as* node = this;
    StringPairs::const_iterator it;
    StringPairs attrs;

    while (node) {

        enumerateAttributes(*node, attrs);

        if (!attrs.empty()) {

            it = std::find_if(attrs.begin(), attrs.end(),
                        boost::bind(prefixMatches, _1, prefix));
            if (it != attrs.end()) break;
        }
        node = node->getParent();
    }


    if (!node) return;


    ns = it->second;

}
