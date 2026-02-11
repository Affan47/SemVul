log(Log* pLog)
    {
        pLog->logMessage("CPU Identifier & Features");
        pLog->logMessage("-------------------------");
        pLog->logMessage(
            " *   CPU ID: " + getCpuIdentifier());
#if OGRE_CPU == OGRE_CPU_X86
        if(_isSupportCpuid())
        {
            pLog->logMessage(
                " *      SSE: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_SSE), true));
            pLog->logMessage(
                " *     SSE2: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_SSE2), true));
            pLog->logMessage(
                " *     SSE3: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_SSE3), true));
            pLog->logMessage(
                " *      MMX: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_MMX), true));
            pLog->logMessage(
                " *   MMXEXT: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_MMXEXT), true));
            pLog->logMessage(
                " *    3DNOW: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_3DNOW), true));
            pLog->logMessage(
                " * 3DNOWEXT: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_3DNOWEXT), true));
            pLog->logMessage(
                " *     CMOV: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_CMOV), true));
            pLog->logMessage(
                " *      TSC: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_TSC), true));
            pLog->logMessage(
                " *      FPU: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_FPU), true));
            pLog->logMessage(
                " *      PRO: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_PRO), true));
            pLog->logMessage(
                " *       HT: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_HTT), true));
        }
#elif OGRE_CPU == OGRE_CPU_ARM || OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
        pLog->logMessage(
                " *      VFP: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_VFP), true));
        pLog->logMessage(
                " *     NEON: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_NEON), true));
#elif OGRE_CPU == OGRE_CPU_MIPS
        pLog->logMessage(
                " *      MSA: " + StringConverter::toString(hasCpuFeature(CPU_FEATURE_MSA), true));
#endif
        pLog->logMessage("-------------------------");

    }
