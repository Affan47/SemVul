operator=(const GenericMatrix& bmx)
{
   if (&bmx != this) { REPORT if (gm) delete gm; gm = bmx.gm->Image();}
   else { REPORT }
   gm->Protect();
}
