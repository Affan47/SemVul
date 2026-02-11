S_save_hek_flags(const char *str, I32 len, U32 hash, int flags)
{
    const int flags_masked = flags & HVhek_MASK;
    char *k;
    HEK *hek;

    PERL_ARGS_ASSERT_SAVE_HEK_FLAGS;

    Newx(k, HEK_BASESIZE + len + 2, char);
    hek = (HEK*)k;
    Copy(str, HEK_KEY(hek), len, char);
    HEK_KEY(hek)[len] = 0;
    HEK_LEN(hek) = len;
    HEK_HASH(hek) = hash;
    HEK_FLAGS(hek) = (unsigned char)flags_masked | HVhek_UNSHARED;

    if (flags & HVhek_FREEKEY)
	Safefree(str);
    return hek;
}
