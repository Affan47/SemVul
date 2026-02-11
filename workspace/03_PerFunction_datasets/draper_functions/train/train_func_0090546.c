genThisBasisMigs(const CglLandP::CachedData &cached,
                                  const CglLandP::Parameters & params)
{
    for (int i = 0 ; i < cached.nBasics_ ; i++)
    {
        const int iCol = basics_[i];
        if (iCol >= ncols_ ||
                !cached.integers_[iCol] ||
                int_val(colsol_[iCol], params.away))
            continue;
        OsiRowCut * cut = new OsiRowCut;
        generateMig(i, *cut, params);
        int code = validator_(*cut, cached.colsol_, *si_, params, &lo_bounds_[0], &up_bounds_[0]);
        if (code)
        {
            delete cut;
            continue;
        }
        cut->setEffectiveness(cut->violated(cached.colsol_));
        if (cuts_.rowCut(iCol) == NULL || cut->effectiveness() > cuts_.rowCut(iCol)->effectiveness())
        {
            cuts_.insert(iCol,cut);
        }
        else
            delete cut;
    }
}
