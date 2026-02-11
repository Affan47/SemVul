vbh_frevbinst( HeadType )

  ptype_list *HeadType;
{
  ptype_list *ScanType;

  for ( ScanType  = HeadType;
        ScanType != (ptype_list *)0;
        ScanType  = ScanType->NEXT )
  {
    switch ( ScanType->TYPE )
    {
      case VBH_BEIFS : vbh_frevbifs( ScanType->DATA );
      break;

      case VBH_BEASG : vbh_frevbasg( ScanType->DATA );
      break;

      case VBH_BEVAR : vbh_frevbvar( ScanType->DATA );
      break;

      case VBH_BECAS : vbh_frevbcas( ScanType->DATA );
      break;

      case VBH_BEWAS : vbh_frevbwas( ScanType->DATA );
      break;

      case VBH_BEWHI : vbh_frevbwhi( ScanType->DATA );
      break;

      case VBH_BELOP : vbh_frevblop( ScanType->DATA );
      break;

      case VBH_BEFOR : vbh_frevbfor( ScanType->DATA );
      break;

      case VBH_BENXT : vbh_frevbnxt( ScanType->DATA );
      break;

      case VBH_BEEXT : vbh_frevbext( ScanType->DATA );
      break;

      case VBH_BECAL : vbh_frevbcal( ScanType->DATA );
      break;

      case VBH_BERET : vbh_frevbret( ScanType->DATA );
      break;

      case VBH_BEAGR : vbh_frevbagr( ScanType->DATA );
    }
  }

  freeptype( HeadType );
}
