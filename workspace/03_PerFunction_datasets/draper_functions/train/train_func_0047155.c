CreateOptionGroup(const string& groupName) {
    OptionGroup og;
    og.Name = groupName;
    m_optionGroups.push_back(og);
    return &m_optionGroups[m_optionGroups.size() - 1];
}
