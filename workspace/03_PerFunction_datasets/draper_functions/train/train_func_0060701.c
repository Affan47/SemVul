getXC(int nElectrons,
                               symmMatrix& xca, symmMatrix& xcb,
                               real* xcEnergy, int nThreads) const
{
    real electrons;

    Util::TimeMeter tm;
    bool isGGA = selected_func->is_gga();

    *xcEnergy = 0.0;
    sync_threads(false, nThreads);
    SparseMatrix mata(*pattern), matb(*pattern);
    struct UksData<Dft::SparseMatrix> ds(&mata, &matb, DFT_MAX_BLLEN);

    void (*cblda)(DftIntegratorBl* grid, real * restrict tmp,
                  int bllen, int blstart, int blend,
                  UksData<SparseMatrix>* data)
      = xcCallbackLdaU<SparseMatrix,XCDistributorLda<SparseMatrix> >;
    void (*cbgga)(DftIntegratorBl* grid, real * restrict tmp,
                  int bllen, int blstart, int blend,
                  UksData<SparseMatrix>* data)
      = xcCallbackGgaU<SparseMatrix,XCDistributorGgaU<SparseMatrix> >;

    electrons = integrate(2, dMat, *bisPermuted, mol, gss,
                          nThreads,
                          DftBlockCallback(isGGA ? cbgga : cblda),
                          &ds);

    pthread_mutex_lock(&dft_prop_mutex);
    *xcEnergy +=ds.energy;
    pthread_mutex_unlock(&dft_prop_mutex);
    mata.addSymmetrizedTo(xca, aoMap, permutationHML);
    matb.addSymmetrizedTo(xcb, aoMap, permutationHML);
    pthread_mutex_unlock(&dft_prop_mutex);

    if(nThreads <= 1) {
      do_output(LOG_CAT_INFO, LOG_AREA_DFT,
                "Electrons: %11.7f %7.1g:  U-xc energy %f (serial)",
                (double)electrons,
                (double)((electrons-nElectrons)/nElectrons),
                (double)ds.energy);
      tm.print(LOG_AREA_DFT, __func__);
    }
    return electrons;
}
