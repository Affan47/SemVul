CmdFontSize(int code)


{
    int scaled_size;

    diagnostics(5, "CmdFontSize (before) depth=%d, family=%d, size=%d, shape=%d, series=%d",
      FontInfoDepth, RtfFontInfo[FontInfoDepth].family,
      RtfFontInfo[FontInfoDepth].size, RtfFontInfo[FontInfoDepth].shape, RtfFontInfo[FontInfoDepth].series);


    if (code == F_SMALLER)
        scaled_size = (int) (CurrentFontSize() / 1.2 + 0.5);
    else if (code == F_LARGER)
        scaled_size = (int) (CurrentFontSize() * 1.2 + 0.5);
    else
        scaled_size = (int) (code * DefaultFontSize() / 20.0 + 0.5);

    fprintRTF("\\fs%d ", scaled_size);

    diagnostics(5, "CmdFontSize (after) depth=%d, family=%d, size=%d, shape=%d, series=%d",
      FontInfoDepth, RtfFontInfo[FontInfoDepth].family,
      RtfFontInfo[FontInfoDepth].size, RtfFontInfo[FontInfoDepth].shape, RtfFontInfo[FontInfoDepth].series);
}
