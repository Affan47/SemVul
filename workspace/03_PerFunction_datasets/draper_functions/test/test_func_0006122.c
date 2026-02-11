write(DcmOutputStream &outStream,
                              const E_TransferSyntax oxfer,
                              const E_EncodingType ,
                              DcmWriteCache *wcache)
{
    DcmWriteCache wcache2;


    if (getTransferState() == ERW_notInitialized)
        errorFlag = EC_IllegalCall;
    else
    {


        errorFlag = outStream.status();
        if (errorFlag.good())
        {

            DcmXfer outXfer(oxfer);


            Uint8 *value = NULL;
            OFBool accessPossible = OFFalse;


            if (getLengthField() > 0)
            {
              if (valueLoaded())
              {


                value = OFstatic_cast(Uint8 *, getValue(outXfer.getByteOrder()));
                if (value) accessPossible = OFTrue;
              }
              else
              {


                if (!wcache) wcache = &wcache2;


                wcache->init(this, getLengthField(), getTransferredBytes(), outXfer.getByteOrder());


                errorFlag = wcache->fillBuffer(*this);


                accessPossible = errorFlag.good() && (! wcache->bufferIsEmpty());
              }
            }


            if (getTransferState() == ERW_init)
            {


                if ((outStream.avail() >= DCM_TagInfoLength) ||
                    (outStream.avail() >= getTagAndLengthSize(oxfer)))
                {

                    if (! accessPossible) setLengthField(0);


                    Uint32 writtenBytes = 0;


                    errorFlag = writeTagAndLength(outStream, oxfer, writtenBytes);


                    if (errorFlag.good())
                    {
                        setTransferState(ERW_inWork);
                        setTransferredBytes(0);
                    }
                } else errorFlag = EC_StreamNotifyClient;
            }


            if (accessPossible && getTransferState() == ERW_inWork)
            {
                Uint32 len = 0;
                if (valueLoaded())
                {


                    len = OFstatic_cast(Uint32, outStream.write(&value[getTransferredBytes()], getLengthField() - getTransferredBytes()));


                    incTransferredBytes(len);


                    errorFlag = outStream.status();
                }
                else
                {
                    Uint32 buflen = 0;
                    OFBool done = getTransferredBytes() == getLengthField();
                    while (! done)
                    {

                      errorFlag = wcache->fillBuffer(*this);
                      buflen = wcache->contentLength();

                      if (errorFlag.good())
                      {

                        len = wcache->writeBuffer(outStream);


                        incTransferredBytes(len);


                        errorFlag = outStream.status();
                      }


                      done = errorFlag.bad() || (len < buflen) || (getTransferredBytes() == getLengthField());
                    }
                }


                if (getLengthField() == getTransferredBytes()) setTransferState(ERW_ready);
                else if (errorFlag.good()) errorFlag = EC_StreamNotifyClient;

            }
        }
    }

    return errorFlag;
}
