setCaretInvisibleIfNeeded(KHTMLPart *part)
{

  if (!khtml::KHTMLPartAccessor::caret(part).caretPos().node()->isContentEditable())
    part->setCaretVisible(false);
}
