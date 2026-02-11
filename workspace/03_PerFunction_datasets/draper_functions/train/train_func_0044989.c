InitDuplexBuffer()
{

    if (RastersOnPage)
       delete [] RastersOnPage;
    if (KRastersOnPage)
       delete [] KRastersOnPage;


    CurrentRaster = ph.height - 1;
    RastersOnPage = (BYTE **) new BYTE[(ph.height) * sizeof (BYTE *)];
    KRastersOnPage = (BYTE **) new BYTE[(ph.height) * sizeof (BYTE *)];
    for (int i = 0; i < ph.height; i++)
    {
       RastersOnPage[i] = NULL;
       KRastersOnPage[i] = NULL;
    }
    return 0;
}
