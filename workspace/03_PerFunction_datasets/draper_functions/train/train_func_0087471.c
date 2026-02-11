try_xcatchall(tst_case *tc)
{
    bool catchall_handled = false;

    TRY
        RAISE(EXCEPTION, msg1);
        Assert(false, "Exception should have been raised");
    XCATCHALL
        HANDLED();
        RAISE(EXCEPTION, msg1);
        catchall_handled = true;
    XENDTRY
    Assert(catchall_handled, "Finally wasn't handled");
    Atrue(catchall_handled);
}
