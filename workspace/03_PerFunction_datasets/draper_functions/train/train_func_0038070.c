setPadDocument(PadDocument *pad)
{
    if (d_th->_pad) {
        disconnectPadDocument();
    }
    disconnectOutputDocumentChanges();
    d_th->_pad = pad;
    textEdit()->setDocument(d_th->_pad->outputDocument());
    connectPadDocument();
    connectOutputDocumentChanges();
    onDocumentAnalyzeReset();
}
