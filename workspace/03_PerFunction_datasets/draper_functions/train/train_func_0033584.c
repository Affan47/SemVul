kmgcry_gethandle()
{
#if HAVE_LIBGCRYPT
#  if USE_MODULES
    KM_GETHANDLE(MOD_PATH, "keymgr_gcry");
#  else
    return &keymgr_gcry;
#  endif
#else
    return NULL;
#endif
}
