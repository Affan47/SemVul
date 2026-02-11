doOutputFindNext(bool directionForward)
{
  if (this->FindHistory.isEmpty())
    {
    doOutputFindDialog();
    return;
    }

  QString search = this->FindHistory.front();

  QTextCursor cursor = this->Output->textCursor();
  QTextDocument* document = this->Output->document();
  QTextDocument::FindFlags flags;
  if (!directionForward)
    {
    flags |= QTextDocument::FindBackward;
    }

  cursor = document->find(search, cursor, flags);

  if (cursor.isNull())
    {

    cursor = this->Output->textCursor();
    cursor.movePosition(directionForward ? QTextCursor::Start
                                         : QTextCursor::End);
    cursor = document->find(search, cursor, flags);
    }

  if (cursor.hasSelection())
    {
    this->Output->setTextCursor(cursor);
    }
}
