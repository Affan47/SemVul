DoDrawBitmap(const class wxBitmap & bmp, wxCoord x, wxCoord y , bool  WXUNUSED(bTransparent)  )
{
    if (m_graphics_changed) NewGraphics ();

    wxString sTmp, s, sPNG ;
    wxImage::AddHandler(new wxPNGHandler);


    sTmp.Printf ( wxT("_image%d.png"), m_sub_images);
    sPNG = m_filename.BeforeLast(wxT('.')) + sTmp;
    while (wxFile::Exists(sPNG) )
    {
        m_sub_images ++ ;
        sTmp.Printf ( wxT("_image%d.png"), m_sub_images);
        sPNG = m_filename.BeforeLast(wxT('.')) + sTmp;
    }


    wxBitmap myBitmap = bmp ;

    bool bPNG_OK = myBitmap.SaveFile(sPNG,wxBITMAP_TYPE_PNG);


    int w = myBitmap.GetWidth();
    int h = myBitmap.GetHeight();
    sTmp.Printf ( wxT(" <image x=\"%d\" y=\"%d\" width=\"%dpx\" height=\"%dpx\" "), x,y,w,h );
    s = s + sTmp ;
    sTmp.Printf ( wxT(" xlink:href=\"%s\"> \n"), sPNG.c_str() );
    s = s + sTmp + wxT("<title>Image from wxSVG</title>  </image>") + newline;

    if (m_OK && bPNG_OK)
    {
        write(s);
    }
    m_OK = m_outfile->Ok () && bPNG_OK;
    wxASSERT_MSG(!wxSVG_DEBUG, wxT("wxSVGFileDC::DoDrawBitmap Call executed")) ;

    return  ;
}
