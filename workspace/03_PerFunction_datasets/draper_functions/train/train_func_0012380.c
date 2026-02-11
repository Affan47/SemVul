writeData (const std::vector<complex<double> >& inData,
                                long firstRow,
                                complex<double>* nullValue)
        {
                int status(0);
                int nRows (inData.size());
                FITSUtil::auto_array_ptr<double> pData(new double[nRows*2]);
                double* Data = pData.get();
                std::vector<complex<double> > __tmp(m_data);
                for (int j = 0; j < nRows; ++j)
                {
                        pData[ 2*j] = inData[j].real();
                        pData[ 2*j + 1] = inData[j].imag();
                }

                try
                {

                        if (fits_write_col_dblcmp(fitsPointer(), index(), firstRow, 1,
                                  nRows,Data, &status) != 0) throw FitsError(status);
                        long elementsToWrite(nRows + firstRow -1);
                        if (elementsToWrite > static_cast<long>(m_data.size()))
                        {

                                m_data.resize(elementsToWrite);
                        }

                        std::copy(inData.begin(),inData.end(),m_data.begin()+firstRow-1);


                        parent()->updateRows();
                }
                catch (FitsError)
                {

                        m_data.resize(__tmp.size());
                        m_data = __tmp;
                }

        }
