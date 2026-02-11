rk_altfill(void *buffer, size_t size, int strong, rk_state *state)
{
    rk_error err;

    err = rk_devfill(buffer, size, strong);
    if (err) {
        rk_fill(buffer, size, state);
    }
    return err;
}
