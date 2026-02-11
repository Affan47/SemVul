reformatList()
{
    QTextCursor cursor = textEdit->textCursor();
    reformatList(cursor.block());
}
