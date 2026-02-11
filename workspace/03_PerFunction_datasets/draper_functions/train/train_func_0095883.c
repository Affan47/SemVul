store_page_setup(ByteStream &str,
                 int dpi,
                 const GRect &grect,
                 int align )
{


  if (options.get_format() == Options::EPS)
    write(str,
          "/page-origstate save def\n"
          "%% -- coordinate system\n"
          "/image-dpi %d def\n"
          "/image-x 0 def\n"
          "/image-y 0 def\n"
          "/image-width  %d def\n"
          "/image-height %d def\n"
          "/coeff 100 image-dpi div def\n"
          "/a11 coeff def\n"
          "/a12 0 def\n"
          "/a13 0 def\n"
          "/a21 0 def\n"
          "/a22 coeff def\n"
          "/a23 0 def\n"
          "[a11 a21 a12 a22 a13 a23] concat\n"
          "gsave 0 0 image-width image-height rectclip\n"
          "%% -- begin printing\n",
          dpi, grect.width(), grect.height() );
  else
    {
      int margin = 0;
      const char *xauto = "false";
      const char *xportrait = "false";
      const char *xfit = "false";
      if (options.get_orientation()==Options::AUTO)
        xauto = "true";
      if (options.get_orientation()==Options::PORTRAIT)
        xportrait = "true";
      if (options.get_zoom()<=0)
        xfit = "true";
      if (options.get_cropmarks())
        margin = 36;
      else if (options.get_frame())
        margin = 6;
      write(str,
            "/page-origstate save def\n"
            "%% -- coordinate system\n"
            "/auto-orient %s def\n"
            "/portrait %s def\n"
            "/fit-page %s def\n"
            "/zoom %d def\n"
            "/image-dpi %d def\n"
            "clippath pathbbox newpath\n"
            "2 index sub exch 3 index sub\n"
            "/page-width exch def\n"
            "/page-height exch def\n"
            "/page-y exch def\n"
            "/page-x exch def\n"
            "/image-x 0 def\n"
            "/image-y 0 def\n"
            "/image-width  %d def\n"
            "/image-height %d def\n"
            "/margin %d def\n"
            "/halign %d def\n"
            "/valign 0 def\n",
            xauto, xportrait, xfit, options.get_zoom(),
            dpi, grect.width(), grect.height(),
            margin, align );
      write(str,
            "%% -- position page\n"
            "auto-orient {\n"
            "  image-height image-width sub\n"
            "  page-height page-width sub\n"
            "  mul 0 ge /portrait exch def\n"
            "} if\n"
            "fit-page {\n"
            "  /page-width page-width margin sub\n"
            "     halign 0 eq { margin sub } if def\n"
            "  /page-height page-height margin sub\n"
            "     valign 0 eq { margin sub } if def\n"
            "  /page-x page-x halign 0 ge { margin add } if def\n"
            "  /page-y page-y valign 0 ge { margin add } if def\n"
            "} if\n"
            "portrait {\n"
            "  fit-page {\n"
            "    image-height page-height div\n"
            "    image-width page-width div\n"
            "    gt {\n"
            "      page-height image-height div /coeff exch def\n"
            "    } {\n"
            "      page-width image-width div /coeff exch def\n"
            "    } ifelse\n"
            "  } {\n"
            "    /coeff 72 image-dpi div zoom mul 100 div def\n"
            "  } ifelse\n"
            "  /start-x page-x page-width image-width\n"
            "    coeff mul sub 2 div halign 1 add mul add def\n"
            "  /start-y page-y page-height image-height\n"
            "    coeff mul sub 2 div valign 1 add mul add def\n"
            "  /a11 coeff def\n"
            "  /a12 0 def\n"
            "  /a13 start-x def\n"
            "  /a21 0 def\n"
            "  /a22 coeff def\n"
            "  /a23 start-y def\n"
            "} { %% landscape\n"
            "  fit-page {\n"
            "    image-height page-width div\n"
            "    image-width page-height div\n"
            "    gt {\n"
            "      page-width image-height div /coeff exch def\n"
            "    } {\n"
            "      page-height image-width div /coeff exch def\n"
            "    } ifelse\n"
            "  } {\n"
            "    /coeff 72 image-dpi div zoom mul 100 div def\n"
            "  } ifelse\n"
            "  /start-x page-x page-width add page-width image-height\n"
            "    coeff mul sub 2 div valign 1 add mul sub def\n"
            "  /start-y page-y page-height image-width\n"
            "    coeff mul sub 2 div halign 1 add mul add def\n"
            "  /a11 0 def\n"
            "  /a12 coeff neg def\n"
            "  /a13 start-x image-y coeff neg mul sub def\n"
            "  /a21 coeff def\n"
            "  /a22 0 def\n"
            "  /a23 start-y image-x coeff mul add def \n"
            "} ifelse\n"
            "[a11 a21 a12 a22 a13 a23] concat\n"
            "gsave 0 0 image-width image-height rectclip\n"
            "%% -- begin print\n");
    }
}
