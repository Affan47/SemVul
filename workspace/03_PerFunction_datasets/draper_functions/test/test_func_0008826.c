TXTupdate (void) {
    if (!txton)
        return;
    if (txtwi == -1)
        viewon ();
    seeni = 0;
    update (txtroot, txtroot->time);
    txtroot->time = Ttime;
    Ttime++;
}
