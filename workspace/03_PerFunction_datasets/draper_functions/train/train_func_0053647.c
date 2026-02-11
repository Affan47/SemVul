FDSGI(int h)
{
 switch(h)
 {
  case GI_CLOSE: FDSClose();break;
  case GI_POWER: FDSInit();break;
 }
}
