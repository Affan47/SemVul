onChoreIdle(FXObject *, FXSelector, void *)
{


  bool ret = _scint->Idle();
  if (ret == false) {
    _scint->SetIdle(false);
  }
  return 1;
}
