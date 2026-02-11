ASCIITable(ExState &) {
    int rc;

    rc = View->MView->Win->PickASCII();
    if (rc != -1)
        return InsertChar(char(rc));

    return 0;
}
