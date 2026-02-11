pid_sanitize_args(PIDArgs *args)
{
    args->proportional = CLAMP(args->proportional, 0.0, 100.0);
    args->integral = CLAMP(args->integral, 0.0, 100.0);
    args->derivative = CLAMP(args->derivative, 0.0, 100.0);
    args->ratio = CLAMP(args->ratio, 1, 1000);
    args->tau = CLAMP(args->tau, 2, 1000);
    args->fpower = CLAMP(args->fpower, 1, 20);
    args->fstrength = CLAMP(args->fstrength, 0.0, 1000.0);
    args->fsetpoint = CLAMP(args->fsetpoint, 0.0, 1000.0);

}
