createConstParamVector3(Vector3 val)
{
    return ParameterPtr((Parameter*)OGRE_NEW ConstParameterVec3(val,
                                                    GCT_FLOAT3,
                                                    Parameter::SPS_UNKNOWN,
                                                    Parameter::SPC_UNKNOWN));
}
