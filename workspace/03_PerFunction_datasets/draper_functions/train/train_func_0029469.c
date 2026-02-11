dependsOnCurrentWorkspace() const {
    Terms::const_iterator it = m_terms.begin(), it_end = m_terms.end();
    for (; it != it_end; ++it) {
        if (((*it)->prop == WORKSPACE || (*it)->prop == WORKSPACENAME) &&
            (*it)->regstr == "[current]")
            return true;
    }
    return false;
}
