loadFromConfigFile( const mrpt::utils::CConfigFileBase &cfg, const std::string &section )
{
    basePSize = cfg.read_double(section,"basePSize", 23, false );
    comLScl = cfg.read_int(section,"comLScl", 0, false );
    comHScl = cfg.read_int(section,"comHScl", 6, false );
    sg1 = cfg.read_double(section,"sg1", 0.5, false );
    sg2 = cfg.read_double(section,"sg2", 7.5, false );
    sg3 = cfg.read_double(section,"sg3", 8.0, false );
    computeDepth = cfg.read_bool(section,"computeDepth", true, false );
    blurImage = cfg.read_bool(section,"blurImage", true, false );
    fx = cfg.read_double(section,"fx",0.0, false);
    cx = cfg.read_double(section,"cx",0.0, false);
    cy = cfg.read_double(section,"cy",0.0, false);
    baseline = cfg.read_double(section,"baseline",0.0, false);
    computeHashCoeffs = cfg.read_bool(section,"computeHashCoeffs", false, false );


    cfg.read_vector(section,"scales",vector<double>(),scales,false);
    if(scales.size() < 1)
    {
        scales.resize(7);
        scales[0] = 0.5;
        scales[1] = 0.8;
        scales[2] = 1.0;
        scales[3] = 1.2;
        scales[4] = 1.5;
        scales[5] = 1.8;
        scales[6] = 2.0;
    }
}
