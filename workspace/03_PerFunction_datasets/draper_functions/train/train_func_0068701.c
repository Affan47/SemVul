caml_extunix_setpriority(value vwprio, value vprio)
{
  CAMLparam2(vwprio, vprio);
  int  which;
  id_t who;

  decode_which_prio(vwprio, &which, &who);

  if (setpriority(which, who, Int_val(vprio)) != 0)
  {
    uerror("setpriority", Nothing);
  }

  CAMLreturn(Val_unit);
}
