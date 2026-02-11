logarithm(void)
{
    double arg;
    arg = POPn;
    if (arg <= 0) runtime_error(_("invalid argument in ln"));
    PSHn(log(POPn));
}
