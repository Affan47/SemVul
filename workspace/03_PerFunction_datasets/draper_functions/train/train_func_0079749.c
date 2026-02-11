caml_weak_check (value ar, value n)
{
  mlsize_t offset = Long_val (n) + 1;
                                                   Assert (Is_in_heap (ar));
  if (offset < 1 || offset >= Wosize_val (ar)){
    caml_invalid_argument ("Weak.get");
  }
  return Val_bool (Field (ar, offset) != caml_weak_none);
}
