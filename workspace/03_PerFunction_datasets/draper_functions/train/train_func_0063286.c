Graphics ()
{

    DRIVER_ERROR err;
    err = thePrinter->Send ((const BYTE*) grafStart, sizeof (grafStart));
    ERRCHECK;

    if (((LJColor *) thePrinter)->bGrey_K)
    {
        err = thePrinter->Send ((const BYTE*) "\033*b2M", 5);
        ERRCHECK;
    }
    else
    {
        err = thePrinter->Send ((const BYTE*) "\033*b3M", 5);
    }

    return err;
}
