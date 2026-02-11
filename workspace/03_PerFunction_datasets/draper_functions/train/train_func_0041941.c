highlightAll()
{
    webView()->findText(QString(), QWebPage::HighlightAllOccurrences);

    if (ui.highlightAllButton->isChecked())
        find(QWebPage::HighlightAllOccurrences);
}
