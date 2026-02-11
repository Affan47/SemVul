ScrollY(int Delta) {


    if (Delta >= Rows || -Delta >= Rows)
        return ;

    if (Delta < 0) {
        Delta = -Delta;
        if (Delta > Rows) return;
        View->MView->ConScroll(csDown, 0, 0, Cols, Rows, hcPlain_Background, Delta);
    } else {
        if (Delta > Rows) return;
        View->MView->ConScroll(csUp, 0, 0, Cols, Rows, hcPlain_Background, Delta);
    }
}
