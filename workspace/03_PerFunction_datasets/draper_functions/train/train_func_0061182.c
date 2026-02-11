unbindGpuProgram(GpuProgramType gptype)
    {

        if (gptype == GPT_VERTEX_PROGRAM && mCurrentVertexProgram)
        {
            mActiveVertexGpuProgramParameters.setNull();
            mCurrentVertexProgram->unbindProgram();
            mCurrentVertexProgram = 0;
        }
        else if (gptype == GPT_GEOMETRY_PROGRAM && mCurrentGeometryProgram)
        {
            mActiveGeometryGpuProgramParameters.setNull();
            mCurrentGeometryProgram->unbindProgram();
            mCurrentGeometryProgram = 0;
        }
        else if (gptype == GPT_FRAGMENT_PROGRAM && mCurrentFragmentProgram)
        {
            mActiveFragmentGpuProgramParameters.setNull();
            mCurrentFragmentProgram->unbindProgram();
            mCurrentFragmentProgram = 0;
        }
        RenderSystem::unbindGpuProgram(gptype);

    }
