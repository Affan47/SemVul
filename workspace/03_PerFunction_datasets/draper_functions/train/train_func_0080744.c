setProgram(GpuProgramPtr& prog)
    {
        mProgram = prog;

        mParameters = mProgram->createParameters();
    }
