GetDocProgress(wxInt32 item, float& fBuffer) const {
    float          fBytesSent = 0;
    float          fFileSize = 0;
    FILE_TRANSFER* transfer = NULL;
    CMainDocument* pDoc = wxGetApp().GetDocument();

    if (pDoc) {
        transfer = pDoc->file_transfer(item);
    }

    fBuffer = 0;
    if (transfer) {
        fBytesSent = transfer->bytes_xferred;
        fFileSize = transfer->nbytes;
    }


    if (fBytesSent > fFileSize) {
        fBytesSent = fFileSize;
    }

    if (fFileSize) {
        fBuffer = floor((fBytesSent / fFileSize) * 10000)/100;
    }
}
