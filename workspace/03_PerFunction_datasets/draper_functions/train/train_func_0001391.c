slotReplaceText(const QString &text, int replacementIndex, int replacedLength, int matchedLength) {

    QTextCursor tc = parent->textCursor();
    tc.setPosition(replacementIndex);
    tc.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, matchedLength);
    tc.removeSelectedText();
    tc.insertText(text.mid(replacementIndex, replacedLength));
    if (replace->options() & KReplaceDialog::PromptOnReplace) {
        parent->setTextCursor(tc);
        parent->ensureCursorVisible();
    }
    lastReplacedPosition = replacementIndex;
}
