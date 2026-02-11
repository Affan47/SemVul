qmfAnalysisFilteringSlot( HANDLE_QMF_FILTER_BANK anaQmf,
                          FIXP_QMF      *qmfReal,
                          FIXP_QMF      *qmfImag,
                          const INT_PCM *RESTRICT timeIn,
                          const int      stride,
                          FIXP_QMF      *pWorkBuffer
                         )
{
    int i;
    int offset = anaQmf->no_channels*(QMF_NO_POLY*2-1);


    {
      FIXP_QAS *RESTRICT FilterStatesAnaTmp = ((FIXP_QAS*)anaQmf->FilterStates)+offset;


      for(i=anaQmf->no_channels>>1; i!=0; i--) {

#if (QAS_BITS==SAMPLE_BITS)
        *FilterStatesAnaTmp++ = (FIXP_QAS)*timeIn; timeIn += stride;
        *FilterStatesAnaTmp++ = (FIXP_QAS)*timeIn; timeIn += stride;
#elif (QAS_BITS>SAMPLE_BITS)
        *FilterStatesAnaTmp++ = (FIXP_QAS)((*timeIn)<<(QAS_BITS-SAMPLE_BITS)); timeIn += stride;
        *FilterStatesAnaTmp++ = (FIXP_QAS)((*timeIn)<<(QAS_BITS-SAMPLE_BITS)); timeIn += stride;
#else
        *FilterStatesAnaTmp++ = (FIXP_QAS)((*timeIn)>>(SAMPLE_BITS-QAS_BITS)); timeIn += stride;
        *FilterStatesAnaTmp++ = (FIXP_QAS)((*timeIn)>>(SAMPLE_BITS-QAS_BITS)); timeIn += stride;
#endif
      }
    }

    if (anaQmf->flags & QMF_FLAG_NONSYMMETRIC) {
      qmfAnaPrototypeFirSlot_NonSymmetric(
                              pWorkBuffer,
                              anaQmf->no_channels,
                              anaQmf->p_filter,
                              anaQmf->p_stride,
                              (FIXP_QAS*)anaQmf->FilterStates
                            );
    } else {
      qmfAnaPrototypeFirSlot( pWorkBuffer,
                              anaQmf->no_channels,
                              anaQmf->p_filter,
                              anaQmf->p_stride,
                              (FIXP_QAS*)anaQmf->FilterStates
                            );
    }

    if (anaQmf->flags & QMF_FLAG_LP) {
      if (anaQmf->flags & QMF_FLAG_CLDFB)
        qmfForwardModulationLP_odd( anaQmf,
                                    pWorkBuffer,
                                    qmfReal );
      else
        qmfForwardModulationLP_even( anaQmf,
                                     pWorkBuffer,
                                     qmfReal );

    } else {
      qmfForwardModulationHQ( anaQmf,
                              pWorkBuffer,
                              qmfReal,
                              qmfImag
                             );
    }


    FDKmemmove ((FIXP_QAS*)anaQmf->FilterStates, (FIXP_QAS*)anaQmf->FilterStates+anaQmf->no_channels, offset*sizeof(FIXP_QAS));
}
