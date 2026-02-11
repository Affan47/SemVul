H5T_lock (H5T_t *dt, hbool_t immutable)
{
    herr_t ret_value=SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    assert (dt);

    switch (dt->shared->state) {
        case H5T_STATE_TRANSIENT:
            dt->shared->state = immutable ? H5T_STATE_IMMUTABLE : H5T_STATE_RDONLY;
            break;
        case H5T_STATE_RDONLY:
            if (immutable) dt->shared->state = H5T_STATE_IMMUTABLE;
            break;
        case H5T_STATE_IMMUTABLE:
        case H5T_STATE_NAMED:
        case H5T_STATE_OPEN:

            break;
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
