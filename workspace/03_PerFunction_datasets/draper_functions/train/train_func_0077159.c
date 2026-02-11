__to_baselet(int32 bcod)
{
 char ch;

 switch ((byte) bcod) {
  case BBIN: ch = 'b'; break;
  case BHEX: ch = 'h'; break;
  case BOCT: ch = 'o'; break;
  case BDEC: ch = 'd'; break;
  default: ch = '?'; __case_terr(__FILE__, __LINE__);
 }
 return(ch);
}
