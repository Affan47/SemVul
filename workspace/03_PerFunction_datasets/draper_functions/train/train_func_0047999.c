createVertexProgram(
        const SM2Profile* prof, const Terrain* terrain, TechniqueType tt)
    {
        HighLevelGpuProgramManager& mgr = HighLevelGpuProgramManager::getSingleton();
        String progName = getVertexProgramName(prof, terrain, tt);
        HighLevelGpuProgramPtr ret = mgr.getByName(progName).staticCast<HighLevelGpuProgram>();
        if (ret.isNull())
        {
            ret = mgr.createProgram(progName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                "cg", GPT_VERTEX_PROGRAM).staticCast<HighLevelGpuProgram>();
        }
        else
        {
            ret->unload();
        }

        ret->setParameter("profiles", "vs_4_0 vs_3_0 vs_2_0 arbvp1");
        ret->setParameter("entry_point", "main_vp");

        return ret;

    }
