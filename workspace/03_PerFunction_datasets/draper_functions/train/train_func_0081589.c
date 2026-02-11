OnPrintPage( int page )
{
  wxDC *dc = GetDC();
  if( dc )
  {

    int ppiScreenX, ppiScreenY;
    GetPPIScreen( &ppiScreenX, &ppiScreenY );
    int ppiPrinterX, ppiPrinterY;
    GetPPIPrinter( &ppiPrinterX, &ppiPrinterY );


    double scale = (double)ppiPrinterX/(double)ppiScreenX;


    int pageWidth, pageHeight;
    int w, h;
    dc->GetSize( &w, &h );
    GetPageSizePixels( &pageWidth, &pageHeight );


    double overallScale = scale*w/(double)pageWidth;
    dc->SetUserScale( overallScale, overallScale );

    long xo=0, yo=0;
    dc->SetDeviceOrigin( xo, yo );
    dc->SetMapMode( wxMM_TEXT );

    int dch = dc->GetPPI().GetHeight();
    int dcw = dc->GetPPI().GetWidth();
    double xminW, yminW, xmaxW, ymaxW;
    ExGlobals::GetWorldLimits( xminW, yminW, xmaxW, ymaxW );
    int xmin = static_cast<int>(xminW*dch+0.5)+50;
    int ymin = static_cast<int>(yminW*dcw+0.5)+50;
    int xmax = static_cast<int>(0.7*xmaxW*dch+0.5)+50;
    int ymax = static_cast<int>(0.7*ymaxW*dcw+0.5)+50;


    dc->StartDoc( wxT("extrema printing...") );
    GRA_wxWidgets ps( xmin, ymin, xmax, ymax );
    try
    {
      ExGlobals::DrawGraphWindows( &ps, *dc );
    }
    catch (EGraphicsError &e)
    {
      wxMessageBox( wxString(e.what(),wxConvUTF8), wxT("error"), wxOK|wxICON_ERROR );
      return false;
    }
    dc->EndDoc();
    return true;
  }
  else return false;
}
