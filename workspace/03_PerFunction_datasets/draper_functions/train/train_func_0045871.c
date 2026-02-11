resolveTemporary() {
    TemporaryCommand * tc = dynamic_cast<TemporaryCommand *>(m_temporary);
    m_temporary = NULL;
    if (tc) {
        tc->setEnabled(false);
        push(tc);
        tc->setEnabled(true);
    }
}
