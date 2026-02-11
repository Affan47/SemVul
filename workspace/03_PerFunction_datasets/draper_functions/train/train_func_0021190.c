readColumnData (long firstRow,
              long nelements,long firstElem,
              complex<double>* nullValue)
    {


            int   status=0;
            double nulval (0);
            FITSUtil::auto_array_ptr<double> pArray(new double[2*nelements]);
            double*     array = pArray.get();
            int    anynul(0);

            if (fits_read_col_dblcmp(fitsPointer(),index(),firstRow, firstElem,
                            nelements,nulval,array,&anynul,&status) ) throw FitsError(status);

            if (m_data.size() != static_cast<size_t>(rows())) m_data.resize(rows());

            std::valarray<std::complex<double> > readData(nelements);
            for (long j = 0; j < nelements; ++j)
            {
                    readData[j] = std::complex<double>(array[2*j],array[2*j+1]);
            }
            size_t countRead = 0;
            const size_t ONE = 1;

            if (m_data.size() != static_cast<size_t>(rows())) m_data.resize(rows());
            size_t vectorSize(0);
            if (!varLength())
            {
                 vectorSize = std::max(repeat(),ONE);
            }
            else
            {


                 vectorSize = nelements;
            }
            size_t n = nelements;

            int i = firstRow;
            int ii = i - 1;
            while ( countRead < n)
            {
                    std::valarray<std::complex<double> >& current = m_data[ii];
                    if (current.size() != vectorSize) current.resize(vectorSize,0.);
                    int elementsInFirstRow = vectorSize-firstElem + 1;
                    bool lastRow = ( (nelements - countRead) < vectorSize);
                    if (lastRow)
                    {
                            int elementsInLastRow = nelements - countRead;
                            std::copy(&readData[countRead],&readData[0]+nelements,&current[0]);
                            countRead += elementsInLastRow;
                    }

                    else
                    {
                            if (firstElem == 1 || (firstElem > 1 && i > firstRow) )
                            {
                                    current = readData[std::slice(vectorSize*(ii-firstRow)+
                                                               elementsInFirstRow,vectorSize,1)];
			            ++ii;
			            ++i;
                                    countRead += vectorSize;
                            }
                            else
                            {
                                    if (i == firstRow)
                                    {
                                            std::copy(&readData[0],&readData[0]+elementsInFirstRow,
                                                                            &current[firstElem]);
                                            countRead += elementsInFirstRow;
                                            ++i;
                                            ++ii;
                                    }
                            }
                    }
            }
    }
