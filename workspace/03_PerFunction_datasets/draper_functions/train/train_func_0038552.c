xorConvert(CTX ctx, knh_conv_t *cv, const char *text, size_t len, kBytes *tobuf)
{
    int i, key;
    kInt *ki = (kInt *)knh_getPropertyNULL(ctx, STEXT("SEED"));
    if (ki != NULL) {
        key = N_toint(ki);
    }
    else {
        key = knh_rand();
        knh_setProperty(ctx, new_String(ctx, "SEED"), (dynamic *)new_Int(ctx, key));
    }
    for (i = 0; i < len; i++) {
        unsigned char c = text[i];
        knh_Bytes_putc(ctx, tobuf, c ^ key);
    }
    return 1;
}
