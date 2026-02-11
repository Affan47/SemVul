init ( int x, int y, int color, int depth )
{
   agmp = (tgraphmodeparameters *) & activegraphmodeparameters;
   oldparams = *agmp ;
   char* cbuf = (char*) malloc ( x * y * depth/8 );
   if ( !cbuf )
      throw fatalgraphicserror ( "could not allocate memory !");

   buf = cbuf;
   for ( int i = 0; i < (x*y*depth/8); i++ )
      cbuf[i] = color;

   agmp->resolutionx   = x   ;
   agmp->resolutiony   = y   ;
   agmp->windowstatus  = 100 ;
   agmp->scanlinelength  = x*depth/8 ;
   agmp->scanlinenumber  = y ;
   agmp->bytesperscanline  = x * depth/8;
   agmp->byteperpix   = depth/8    ;
   agmp->linearaddress = (PointerSizedInt) buf ;
   agmp->bitperpix          = depth;
   agmp->directscreenaccess = 1;
   if ( depth ==24 || depth==32 ) {
      agmp->redmasksize = 8;
      agmp->greenmasksize = 8;
      agmp->bluemasksize = 8;
      agmp->redfieldposition = 0;
      agmp->greenfieldposition = 8;
      agmp->bluefieldposition = 16;
      surface = agmp->surface = new Surface (  Surface::CreateSurface( buf, x, y, depth, 0xff, 0xff00, 0xff0000) );
   } else {
      surface = agmp->surface = new Surface ( Surface::CreateSurface( buf, x, y, depth, agmp->scanlinelength ) );
      agmp->surface->assignDefaultPalette();
   }

}
