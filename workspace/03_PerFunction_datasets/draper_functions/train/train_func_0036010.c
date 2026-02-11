H5T_is_sensible(const H5T_t *dt)
{
    htri_t	ret_value;

    FUNC_ENTER_NOAPI(H5T_is_sensible, FAIL);

    assert(dt);

    switch(dt->shared->type) {
        case H5T_COMPOUND:

            if(dt->shared->u.compnd.nmembs > 0)
                ret_value=TRUE;
            else
                ret_value=FALSE;
            break;

        case H5T_ENUM:

            if(dt->shared->u.enumer.nmembs > 0)
                ret_value=TRUE;
            else
                ret_value=FALSE;
            break;

        default:

            ret_value=TRUE;
            break;
    }

done:
    FUNC_LEAVE_NOAPI(ret_value);
}
