caml_callback2 (value closure, value arg1, value arg2)
{
  value res = caml_callback2_exn(closure, arg1, arg2);
  if (Is_exception_result(res)) caml_raise(Extract_exception(res));
  return res;
}
