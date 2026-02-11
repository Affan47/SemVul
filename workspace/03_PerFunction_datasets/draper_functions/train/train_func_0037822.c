Reset()
{
    color = trpgColor(1,1,1);
    ambient = trpgColor(0,0,0);
    diffuse = trpgColor(1,1,1);
    specular = trpgColor(0,0,0);
    emission = trpgColor(0,0,0);
    shininess = 0;
    shadeModel = 999;
    pointSize = 1;
    lineWidth = 1;
    cullMode = Back;
    alphaFunc = GreaterThan;
    alphaRef = 0;
    alpha = 1.0;
    autoNormal = false;
    numTex = 0;
    texids.resize(0);
    texEnvs.resize(0);
    numTile = 0;
    isBump = false;
    attrSet.fid = -1;
    attrSet.smc = -1;
    attrSet.stp = -1;
    attrSet.swc = -1;
    handle = -1;
    writeHandle = false;
}
