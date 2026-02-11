writeProperty(const string &property,
                                      const InitStateString &newvalue,
                                      const string &comment) {
    string newstr;
    string oldvalue;
    bool isDefault = false;

    if (!newvalue.wasSet()) {
        newstr += "# ";
        isDefault = true;
    }
    newstr += property + " = " + newvalue;

    BOOST_FOREACH(string &line, m_lines) {
        bool isComment;

        if (getValue(line, property, oldvalue, isComment, true)) {
            if (newvalue != oldvalue ||
                (isComment && !isDefault)) {
                line = newstr;
                m_modified = true;
            }
            return;
        }
    }


    if (comment.size()) {
        list<string> commentLines;
        ConfigProperty::splitComment(comment, commentLines);
        if (m_lines.size()) {
            m_lines.push_back("");
        }
        BOOST_FOREACH(const string &comment, commentLines) {
            m_lines.push_back(string("# ") + comment);
        }
    }

    m_lines.push_back(newstr);
    m_modified = true;
}
