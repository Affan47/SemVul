EndPage ()
{
    DRIVER_ERROR err;


	err = thePrinter->Send ((const BYTE*)FrEndPageSeq,sizeof(FrEndPageSeq));
	ERRCHECK;

    return err;
}
