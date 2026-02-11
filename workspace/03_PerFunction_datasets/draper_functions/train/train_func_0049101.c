getParamString() const {
	return "ChangeTagsCommand " +
        QString(" old:%1, new:%2")
            .arg(m_old.count())
            .arg(m_new.count())
        ;
}
