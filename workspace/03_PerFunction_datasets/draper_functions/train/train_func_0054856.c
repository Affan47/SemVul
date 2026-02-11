rfio_xysock(lun)
int lun ;
{
   if ( ftnlun[lun] == NULL )
      return -1 ;
   else
      return ftnlun[lun]->s ;
}
