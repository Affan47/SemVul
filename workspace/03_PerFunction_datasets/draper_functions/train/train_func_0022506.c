writeOutParameters(std::ostream& os, Function* function, GpuProgramType gpuType)
{
    const ShaderParameterList& outParams = function->getOutputParameters();

    ShaderParameterConstIterator itParam = outParams.begin();
    ShaderParameterConstIterator itParamEnd = outParams.end();

    for ( ; itParam != itParamEnd; ++itParam)
    {
        ParameterPtr pParam = *itParam;

        if(gpuType == GPT_VERTEX_PROGRAM)
        {

            if(pParam->getContent() == Parameter::SPC_POSITION_PROJECTIVE_SPACE)
            {
                mInputToGLStatesMap[pParam->getName()] = "gl_Position";
            }
            else
            {

                if(mGLSLVersion <= 120)
                {
                    os << "varying\t";
                }
                else
                {
                    os << "out\t";
                }

                os << mGpuConstTypeMap[pParam->getType()];
                os << "\t";
                os << pParam->getName();
                if (pParam->isArray() == true)
                {
                    os << "[" << pParam->getSize() << "]";
                }
                os << ";" << std::endl;
            }
        }
        else if(gpuType == GPT_FRAGMENT_PROGRAM &&
                pParam->getSemantic() == Parameter::SPS_COLOR)
        {


            if(mGLSLVersion <= 130)
            {
                mInputToGLStatesMap[pParam->getName()] = "gl_FragColor";
            }
            else
            {
                os << "out vec4 fragColour;" << std::endl;
                mInputToGLStatesMap[pParam->getName()] = "fragColour";
            }
        }
    }

    if(gpuType == GPT_VERTEX_PROGRAM)
    {

        if(Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(RSC_SEPARATE_SHADER_OBJECTS) &&
           mGLSLVersion >= 150)
        {
            os << "out gl_PerVertex\n{\nvec4 gl_Position;\nfloat gl_PointSize;\nfloat gl_ClipDistance[];\n};\n" << std::endl;
        }
    }
}
