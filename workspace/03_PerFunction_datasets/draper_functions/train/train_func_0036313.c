_dxfSetInteractorBox (tdmInteractorWin W, float box[8][3])
{
  int i ;
  tdmInteractorCam C ;

  ENTRY(("_dxfSetInteractorBox(0x%x, 0x%x)", W, box));


  if (!W || !(C = W->Cam)) goto error ;

  for (i = 0 ; i < 8 ; i++)
    {
      VPRINT(box[i]);
      C->box[i][0] = box[i][0] ;
      C->box[i][1] = box[i][1] ;
      C->box[i][2] = box[i][2] ;
    }

  C->box_state++ ;
  EXIT((""));
  return ;

 error:

  EXIT(("error"));
  return;
}
