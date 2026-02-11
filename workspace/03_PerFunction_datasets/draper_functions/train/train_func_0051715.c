__dtft_getStringFormat ( CMPIDateTime * dt,
					     CMPIStatus * rc )
{
    struct native_datetime * ndt   = (struct native_datetime *) dt;

    CMSetStatus ( rc, CMPI_RC_OK );
    return native_new_CMPIString(ndt->cimDt, rc);
}
