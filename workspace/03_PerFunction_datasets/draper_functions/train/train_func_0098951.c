addParameter(std::string name, exp_ptr e, unsigned depth)
{
    static const char* const KnownParams[] = {
        "CF::AllowOverlap",
        "CF::Alpha",
        "CF::Background",
        "CF::BorderDynamic",
        "CF::BorderFixed",
        "CF::Color",
        "CF::ColorDepth",
        "CF::Frame",
        "CF::FrameTime",
        "CF::Impure",
        "CF::MaxNatural",
        "CF::MinimumSize",
        "CF::Size",
        "CF::Symmetry",
        "CF::Tile",
        "CF::Time"
    };

    if (!std::binary_search(KnownParams, KnownParams + sizeof(KnownParams)/sizeof(KnownParams[0]), name.c_str(), stringcompare))
        return false;
    ASTmodification* m = dynamic_cast<ASTmodification*> (e.get());
    int varNum = encodeShapeName(name);
    std::map<int, ConfigParam*>::iterator elem = m_ConfigParameters.find(varNum);
    if (elem == m_ConfigParameters.end()) {
        m_ConfigParameters.insert(make_pair(varNum, new ConfigParam(depth, e.release()->simplify())));
    } else {
        if (depth < elem->second->first) {
            elem->second->first = depth;
            elem->second->second = e.release()->simplify();
        } else {
            return true;
        }

    }
    if (name == "CF::Background" && m)
        usesAlpha = m->flags & CF_USES_ALPHA;
    return true;
}
