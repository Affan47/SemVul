ReadLights()
{
    if (!M2MLights.empty())
    {
        M2MLights.clear();
    }

    MeshFile->seek(header.Lights.ofs);

    for(u32 i=0;i<header.Lights.num;i++)
    {
        Light tempLight;
        MeshFile->read(&tempLight,16);
        ReadABlock(tempLight.AmbientColor,ABDT_FLOAT,3);
        ReadABlock(tempLight.AmbientIntensity,ABDT_FLOAT,1);
        ReadABlock(tempLight.DiffuseColor,ABDT_FLOAT,3);
        ReadABlock(tempLight.DiffuseIntensity,ABDT_FLOAT,1);
        ReadABlock(tempLight.AttenuationStart,ABDT_FLOAT,1);
        ReadABlock(tempLight.AttenuationEnd,ABDT_FLOAT,1);
        ReadABlock(tempLight.Unknown,ABDT_INT,1);
        M2MLights.push_back(tempLight);
    }
}
