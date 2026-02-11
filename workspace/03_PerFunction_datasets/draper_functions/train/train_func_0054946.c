copy()
{
    static QClipboard* clipboard = QApplication::clipboard();

    clipboard->setText( selection_.getSelectedText( logData ) );
}
