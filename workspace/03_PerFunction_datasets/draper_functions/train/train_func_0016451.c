SelectAll () {
    selcount = 0;
    for (int i = 0; i < strcount; ++i) {
        BufInsert(strbuf[i], i, selbuf, selbufsize, selcount);
    }
    display->Draw(output, canvas);
    display->Style(0, 0, strcount, -1, highlight);
}
