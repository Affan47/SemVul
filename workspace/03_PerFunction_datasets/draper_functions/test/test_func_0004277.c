_dxfDisassociateInteractorEcho (tdmInteractorWin W, tdmInteractor A)
{
  int i ;

  ENTRY(("_dxfDisassociateInteractorEcho(0x%x, 0x%x)", W, A));


  if (!W || !A || !IS_AUX(A)) {
    EXIT((""));
    return ;
  }

  for (i = 0 ; i < W->numAllocated ; i++)
      if (IS_USED(W->Interactors[i]) && AUX(W->Interactors[i]) == A)
	  AUX(W->Interactors[i]) = (tdmInteractor) 0 ;

  IS_AUX(A) = 0 ;

  EXIT((""));
}
