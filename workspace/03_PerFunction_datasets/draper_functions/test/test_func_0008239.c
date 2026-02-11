handleBeforeKeyPressEvent(QKeyEvent *event)
{
    QTextCursor cursor = textEdit->textCursor();


    if ((event->key() != Qt::Key_Backspace)
            || (!cursor.currentList()))
        return false;

    bool handled = false;

    if (!cursor.hasSelection()
            && cursor.currentList()
            && event->key() == Qt::Key_Backspace
            && cursor.atBlockStart()) {
        handleOnIndentLess();
        handled = true;
    }

    if (cursor.hasSelection()
            && cursor.currentList()
            && event->key() == Qt::Key_Backspace
            && cursor.atBlockStart()) {


        cursor.removeSelectedText();
        handled = true;
    }

    return handled;
}
