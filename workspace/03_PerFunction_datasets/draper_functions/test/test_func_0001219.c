InitBitmaps()
  {
    int     i;

    pix.gray = MakePixmap( gray_bits, gray_width, gray_height,
     colors.white, colors.black );

    pix.xpat = MakePixmap( xpat_bits, xpat_width, xpat_height, colors.traces,
     colors.black );

    pix.select = MakePixmap( select_bits, select_width, select_height,
     colors.banner_fg, colors.banner_bg );

    for( i = 0; i < 3; i++ )
      {
	pix.tops[i] = MakePixmap( tops_bits[i], 3, 2,
	 colors.traces, colors.black);
	pix.bots[i] = MakePixmap( bots_bits[i], 3, 2,
	 colors.traces, colors.black);
      }

#ifndef TCL_IRSIM


    pix.left_arrows = MakePixmap( left_arrows_bits, left_arrows_width,
     left_arrows_height, colors.black, colors.white );

    pix.right_arrows = MakePixmap( right_arrows_bits, right_arrows_width,
     right_arrows_height, colors.black, colors.white );

    pix.chk = MakePixmap( chk_bits, chk_width, chk_height, colors.black,
     colors.white );

    pix.iconbox = MakePixmap( iconbox_bits, iconbox_width, iconbox_height,
     colors.banner_fg, colors.banner_bg );

    pix.sizebox = MakePixmap( sizebox_bits, sizebox_width, sizebox_height,
     colors.banner_fg, colors.banner_bg );

    pix.icon = InitIconBitmap();

#endif

  }
