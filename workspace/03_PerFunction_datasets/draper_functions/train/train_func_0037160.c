removeFromSession(const QStringList& words)
{
	if (m_dictionary) {
		foreach (const QString& word, words) {
			QByteArray word_utf8 = word.toUtf8();
			enchant_dict_remove_from_session(m_dictionary, word_utf8.constData(), word_utf8.length());
		}
	}
}
