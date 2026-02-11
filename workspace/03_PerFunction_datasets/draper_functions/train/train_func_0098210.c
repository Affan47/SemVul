H5T_lock (H5T_t *dt, hbool_t immutable)
{
    herr_t ret_value=SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    HDassert (dt);

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
        default:
            HGOTO_ERROR(H5E_DATATYPE, H5E_BADTYPE, FAIL, "invalid datatype state")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
