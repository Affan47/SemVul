divide(void)
{
    double arg;
    arg = POPn;
    if (arg == 0) runtime_error(_("division by zero"));
    PSHn(POPn / arg);
}
