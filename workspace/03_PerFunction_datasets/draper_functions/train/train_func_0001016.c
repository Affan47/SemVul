jit_init (pTHX)
{
  dSP;
  SV *load, *save;
  char *map_base;
  char *load_ptr, *save_ptr;
  STRLEN load_len, save_len, map_len;
  int count;

  eval_pv ("require 'Coro/jit-" CORO_JIT_TYPE ".pl'", 1);

  PUSHMARK (SP);
  #define VARx(name,expr,type) pushav_4uv (aTHX_ (UV)&(expr), sizeof (expr), offsetof (perl_slots, name), sizeof (type));
  #include "state.h"
  count = call_pv ("Coro::State::_jit", G_ARRAY);
  SPAGAIN;

  save = POPs; save_ptr = SvPVbyte (save, save_len);
  load = POPs; load_ptr = SvPVbyte (load, load_len);

  map_len = load_len + save_len + 16;

  map_base = mmap (0, map_len, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  assert (("Coro: unable to mmap jit code page, cannot continue.", map_base != (char *)MAP_FAILED));

  load_perl_slots = (load_save_perl_slots_type)map_base;
  memcpy (map_base, load_ptr, load_len);

  map_base += (load_len + 15) & ~15;

  save_perl_slots = (load_save_perl_slots_type)map_base;
  memcpy (map_base, save_ptr, save_len);


  mprotect (map_base, map_len, PROT_READ | PROT_EXEC);

  PUTBACK;
  eval_pv ("undef &Coro::State::_jit", 1);
}
