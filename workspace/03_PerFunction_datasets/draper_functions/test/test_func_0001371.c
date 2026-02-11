eraseMemberAssignments(const unsigned int varId, std::map<unsigned int, std::set<unsigned int> > &membervars, std::map<unsigned int, const Token*> &varAssignments)
{
    const std::map<unsigned int, std::set<unsigned int> >::const_iterator it = membervars.find(varId);
    if (it != membervars.end()) {
        const std::set<unsigned int> v = it->second;
        for (std::set<unsigned int>::const_iterator vit = v.begin(); vit != v.end(); ++vit) {
            varAssignments.erase(*vit);
            if (*vit != varId)
                eraseMemberAssignments(*vit, membervars, varAssignments);
        }
    }
}
