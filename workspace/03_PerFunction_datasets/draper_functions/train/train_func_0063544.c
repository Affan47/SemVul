configure(const YRect &r) {
    YWindow::configure(r);

    int ht = height();
    int leftX = 0;
    for (int w = 0; w < workspaceCount; w++) {
        YButton *wk = fWorkspaceButton[w];

        if (wk) {
            wk->setGeometry(YRect(leftX, 0, wk->width(), ht));
            leftX += wk->width();
        }
    }
}
