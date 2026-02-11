ffi_prep_closure_loc (ffi_closure* closure,
		      ffi_cif* cif,
		      void (*fun)(ffi_cif*, void*, void**, void*),
		      void *user_data,
		      void *codeloc)
{
  volatile unsigned short *tramp;


  {
    int abi = cif->abi;
    if (UNLIKELY (! (abi > FFI_FIRST_ABI && abi < FFI_LAST_ABI)))
      return FFI_BAD_ABI;
  }

  tramp = (volatile unsigned short *) &closure->tramp[0];

  tramp[0] = 0xbb49;
  *(void * volatile *) &tramp[1] = ffi_closure_unix64;
  tramp[5] = 0xba49;
  *(void * volatile *) &tramp[6] = codeloc;


  tramp[10] = cif->flags & (1 << 11) ? 0x49f9 : 0x49f8;

  tramp[11] = 0xe3ff;

  closure->cif = cif;
  closure->fun = fun;
  closure->user_data = user_data;

  return FFI_OK;
}
