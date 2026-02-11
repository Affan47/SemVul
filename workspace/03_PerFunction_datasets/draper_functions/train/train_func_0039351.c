recreateParameters()
    {

        GpuProgramParametersSharedPtr savedParams = mParameters;


        mParameters = mProgram->createParameters();


        if (!savedParams.isNull())
            mParameters->copyMatchingNamedConstantsFrom(*savedParams.get());

        mRecreateParams = false;

    }
