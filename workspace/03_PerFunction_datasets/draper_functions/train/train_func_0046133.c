CommandExportPositionPNG(char *sz)
{
    sz = NextToken(&sz);

    if (!CheckGameExists())
        return;

    if (!sz || !*sz) {
        outputl(_("You must specify a file to export to."));
        return;
    }

    if (!confirmOverwrite(sz, fConfirmSave))
        return;


#if USE_BOARD3D
    if (GetMainAppearance()->fDisplayType == DT_3D) {
        GenerateImage3d(sz, exsExport.nPNGSize, BOARD_WIDTH, BOARD_HEIGHT);
    } else
#endif
    {
        renderimages ri;
        renderdata rd;

        CopyAppearance(&rd);
        rd.nSize = exsExport.nPNGSize;

        g_assert(rd.nSize >= 1);

        RenderImages(&rd, &ri);

        GenerateImage(&ri, &rd, msBoard(), sz,
                      exsExport.nPNGSize, BOARD_WIDTH, BOARD_HEIGHT, 0, 0,
                      ms.fMove, ms.fTurn, fCubeUse, ms.anDice, ms.nCube, ms.fDoubled, ms.fCubeOwner);

        FreeImages(&ri);
    }
}
