Gpm_UseRoi(Gpm_Roi *new)
{

  new->prev      =     new->next=NULL;
  new->owned=1;


  if (!gpm_roi && !gpm_handler)
	gpm_handler=Gpm_HandleRoi;

  return Gpm_RaiseRoi(new,NULL);
}
