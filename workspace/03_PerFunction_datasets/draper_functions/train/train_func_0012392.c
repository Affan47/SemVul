get_keycode(const char *name)
{
    Keycode *keycode;

    keycode = (Keycode *)bsearch(name, keycodes, N_KEYCODES,
        sizeof(Keycode), cstrstructcmp);
    return !keycode ? NULL : keycode->code ? keycode->code : "";
}
