chk_delay_cb(p_cb_data datp, struct h_t *hp)
{

 if (hp != NULL)
  {
   if (!__validate_nonit_handle("delay vpi_register_cb", hp)) return(FALSE);
  }

 if (datp->reason != cbNextSimTime)
  {
   if (datp->time == NULL)
    {
     __vpi_err(1934, vpiError,
      "delay vpi_register_cb p_cb_data record required time field missing");
     return(FALSE);
    }

   if (!__validate_time_type("delay call back", datp->time->type))
    return(FALSE);
   if (datp->time->type == vpiSuppressTime)
    {
     __vpi_err(1935, vpiError,
      "delay vpi_register_cb p_cb_data record time field type vpiSuppress field illegal");
      return(FALSE);
    }
  }

 return(TRUE);
}
