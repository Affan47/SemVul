vqt_name(int handle, int index, char *fontname)
{
  DEFINE_VPB;
  int i;

  o_vdipb.intin[0] = (short)index;

  o_vdipb.contrl[VDI_HANDLE] = handle;
  o_vdipb.contrl[ROUTINE] = 130;
  o_vdipb.contrl[N_PTSIN] = 0;
  o_vdipb.contrl[N_INTIN] = 1;
  vdi_call(&o_vdipb);

  for(i=0 ; i<33 ; i++)
    fontname[i] = o_vdipb.intout[i + 1];

  return o_vdipb.intout[0];
}
