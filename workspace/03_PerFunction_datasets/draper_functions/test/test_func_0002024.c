read(DcmInputStream &inStream,
                             const E_TransferSyntax xfer,
                             const E_GrpLenEncoding glenc,
                             const Uint32 maxReadLength)
{

    errorFlag = inStream.status();


    if (errorFlag.good() && inStream.eos())
        errorFlag = EC_EndOfStream;


    else if (errorFlag.good() && getTransferState() != ERW_ready)
    {

        if (getTransferState() == ERW_init)
        {
            if (dcmAutoDetectDatasetXfer.get())
            {


                switch( xfer )
                {
                    case EXS_Unknown:
                    case EXS_LittleEndianImplicit:
                    case EXS_LittleEndianExplicit:
                    case EXS_BigEndianExplicit:
                    case EXS_BigEndianImplicit:
                        Xfer = checkTransferSyntax(inStream);
                        if ((xfer != EXS_Unknown) && (Xfer != xfer))
                            DCMDATA_WARN("DcmDataset: Wrong transfer syntax specified, detecting from dataset");
                        break;
                    default:
                        Xfer = xfer;
                }
            }
            else
            {


                if (xfer == EXS_Unknown)
                    Xfer = checkTransferSyntax(inStream);
                else
                    Xfer = xfer;
            }

            DcmXfer xf(Xfer);
            E_StreamCompression sc = xf.getStreamCompression();
            switch (sc)
            {
                case ESC_none:

                  break;
                case ESC_unsupported:

                  if (errorFlag.good())
                      errorFlag = EC_UnsupportedEncoding;
                  break;
                default:

                  errorFlag = inStream.installCompressionFilter(sc);
                  break;
            }
        }

        if (errorFlag.good())
            errorFlag = DcmItem::read(inStream, Xfer, glenc, maxReadLength);
    }


    if (errorFlag.good() || errorFlag == EC_EndOfStream)
    {

        errorFlag = EC_Normal;


        computeGroupLengthAndPadding(glenc, EPD_noChange, Xfer);


        setTransferState(ERW_ready);
    }


    DCMDATA_TRACE("DcmDataset::read() returns error = " << errorFlag.text());


    return errorFlag;
}
