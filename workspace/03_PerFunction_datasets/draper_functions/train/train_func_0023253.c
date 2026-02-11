setFocusMode(QAction* action)
{
	int focus_mode = action->data().toInt();
	foreach (Document* document, m_documents) {
		document->setFocusMode(focus_mode);
	}
}
