vdi_characters(VDI_Workstation *vwk)
{
  if(vdi_charfuncs[vdipb->contrl[SUBROUTINE]] &&
     (vdipb->contrl[SUBROUTINE] <= 17) && (vdipb->contrl[SUBROUTINE] >= 0))
    vdi_charfuncs[vdipb->contrl[SUBROUTINE]](vwk);
  else
    EDEBUG("vdi_characters: Subroutine %d doesn't exist!\n",vdipb->contrl[SUBROUTINE]);
}
