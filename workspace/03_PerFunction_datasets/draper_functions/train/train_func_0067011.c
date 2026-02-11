loadFromConfigFile( const mrpt::utils::CConfigFileBase &cfg, const std::string &section )
{

    useOriFilter = cfg.read_bool(section,"useOriFilter",true,false);
    oriThreshold = cfg.read_double(section,"oriThreshold",0.2,false);
    lastSeenThreshold = cfg.read_int(section,"lastSeenThreshold",10,false);
    timesSeenThreshold = cfg.read_int(section,"timesSeenThreshold",5,false);
    minFeaturesToFind = cfg.read_int(section,"minFeaturesToFind",5,false);
    minFeaturesToBeLost = cfg.read_int(section,"minFeaturesToBeLost",5,false);

    useDepthFilter = cfg.read_bool(section,"useDepthFilter",true,false);

    matchingThreshold = cfg.read_double(section,"matchingThreshold",1e4,false);
    matchingRatioThreshold = cfg.read_double(section,"matchingRatioThreshold",0.5,false);

    lowScl1 = cfg.read_int(section,"lowScl1",0,false);
    lowScl2 = cfg.read_int(section,"lowScl1",0,false);
    highScl1 = cfg.read_int(section,"highScl1",6,false);
    highScl2 = cfg.read_int(section,"highScl2",6,false);

    searchAreaSize = cfg.read_double(section,"searchAreaSize",20,false);
}
