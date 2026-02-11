caml_callback3 (value closure, value arg1, value arg2,
                                 value arg3)
{
  value res = caml_callback3_exn(closure, arg1, arg2, arg3);
  if (Is_exception_result(res)) caml_raise(Extract_exception(res));
  return res;
}
