LineSplit() {
    if (SplitLine(VToR(CP.Row), CP.Col) == 0) return 0;
    if (BFI(this, BFI_Trim))
	if (TrimLine(VToR(CP.Row)) == 0) return 0;
    return 1;
}
