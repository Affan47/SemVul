timerFinished()
{
	if (!isEditing()) {
		updateCounts();
		qDeleteAll(m_deltas);
		m_deltas.clear();

		QStringList details;
		details << tr("<b>Words:</b> %L1").arg(m_word_count);
		details << tr("<b>Pages:</b> %L1").arg(m_page_count);
		details << tr("<b>Paragraphs:</b> %L1").arg(m_paragraph_count);
		details << tr("<b>Characters:</b> %L1 / %L2").arg(m_character_count).arg(m_character_and_space_count);

		remove();
		m_documents->alerts()->addAlert(new Alert(Alert::NoIcon, m_display_label->text(), details, true));
	}
}
