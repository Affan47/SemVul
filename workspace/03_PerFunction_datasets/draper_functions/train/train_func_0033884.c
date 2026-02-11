saveDocument(int index)
{
	Document* document = m_documents->document(index);
	if (!document->text()->document()->isModified()) {
		return true;
	}


	if (m_auto_save && document->text()->document()->isModified() && !document->filename().isEmpty()) {
		return document->save();
	}


	switch (QMessageBox::question(this, tr("Question"), tr("Save changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Cancel)) {
	case QMessageBox::Save:
		return document->save();
	case QMessageBox::Discard:
		document->text()->document()->setModified(false);
		m_current_wordcount -= document->wordCountDelta();
		return true;
	case QMessageBox::Cancel:
	default:
		return false;
	}
}
