icalparameter_get_fmttype(icalparameter* param)
{
   icalerror_clear_errno();
    icalerror_check_arg_rz( (param!=0), "param");
    return (const char*)((struct icalparameter_impl*)param)->string;
}
