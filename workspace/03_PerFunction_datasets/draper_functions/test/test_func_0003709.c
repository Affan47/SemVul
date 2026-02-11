caml_extunix_ptrace(value v_pid, value v_req)
{
  CAMLparam2(v_pid, v_req);
  long r = 0;
  switch (Int_val(v_req))
  {
    case 0 : r = ptrace(PTRACE_ATTACH, Int_val(v_pid), 0, 0); break;
    case 1 : r = ptrace(PTRACE_DETACH, Int_val(v_pid), 0, 0); break;
    default : caml_invalid_argument("ptrace");
  }
  if (r != 0)
    uerror("ptrace", Nothing);
  CAMLreturn(Val_unit);
}
