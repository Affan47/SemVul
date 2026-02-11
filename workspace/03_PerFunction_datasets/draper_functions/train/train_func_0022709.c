addTable()
{
    TableDialog dialog(this);
    if (dialog.exec() == QDialog::Rejected)
        return;

    QTextCursor cursor(textEdit()->textCursor());

    QTextTable *table = cursor.insertTable(dialog.rows(), dialog.cols(), dialog.format());


    if (dialog.format().headerRowCount()) {
        int i = 0;
        for (i = 0; i < dialog.cols() ; ++i) {
            QTextCharFormat txtformat = table->cellAt(0, i).format();
            txtformat.setFontWeight(QFont::Bold);
            txtformat.setFontItalic(true);
            table->cellAt(0, i).setFormat(txtformat);
            textEdit()->setTextCursor(table->cellAt(0, i).firstCursorPosition()) ;
            textEdit()->setAlignment(Qt::AlignCenter);
        }
    }
    textEdit()->setTextCursor(cursor);
}
