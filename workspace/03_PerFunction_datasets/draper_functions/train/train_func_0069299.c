writeFixedArray
                        (complex<float>* data, long nElements, long nRows, long firstRow,
                         complex<float>* nullValue)
        {

                int status(0);


                if ( nElements < nRows*static_cast<long>(repeat()) )
                {
#ifdef SSTREAM_DEFECT
                        std::ostrstream msgStr;
#else
                        std::ostringstream msgStr;
#endif
                        msgStr << " input array size: " << nElements
                                        << " required " << nRows*repeat();
#ifdef SSTREAM_DEFECT
                        msgStr << std::ends;
#endif


                        String msg(msgStr.str());

                        throw Column::InsufficientElements(msg);
                }

                FITSUtil::auto_array_ptr<float> realData(new float[2*nElements]);

                for (int j = 0; j < nElements; ++j)
                {
                        realData[2*j] = data[j].real();
                        realData[2*j+1] = data[j].imag();
                }


                if (fits_write_col_cmp(fitsPointer(),index(),firstRow,
                        1,nElements,realData.get(),&status)) throw FitsError(status);

                parent()->updateRows();
        }
