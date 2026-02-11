GetProgressValue(long item) {
    double          fBytesSent = 0;
    double          fFileSize = 0;
    FILE_TRANSFER* transfer = NULL;
    CMainDocument* pDoc = wxGetApp().GetDocument();

    if (pDoc) {
        transfer = pDoc->file_transfer(m_iSortedIndexes[item]);
    }

    if (transfer) {
        fBytesSent = transfer->bytes_xferred;
        fFileSize = transfer->nbytes;
    }


    if (fBytesSent > fFileSize) {
        fBytesSent = fFileSize;
    }

    if ( 0.0 == fFileSize ) return 0.0;

    return (fBytesSent / fFileSize);
}
