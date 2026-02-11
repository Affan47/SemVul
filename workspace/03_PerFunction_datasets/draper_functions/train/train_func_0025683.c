Scm_ReadBlockX(ScmUVector *v, ScmPort *port,
                      int start, int end, ScmSymbol *endian)
{
    int len = SCM_UVECTOR_SIZE(v), eltsize, r;

    SCM_CHECK_START_END(start, end, len);
    SCM_UVECTOR_CHECK_MUTABLE(v);
    CHECK_ENDIAN(endian);

    eltsize = Scm_UVectorElementSize(Scm_ClassOf(SCM_OBJ(v)));
    SCM_ASSERT(eltsize >= 1);
    r = Scm_Getz((char*)v->elements + start*eltsize,
                 (end-start)*eltsize, port);
    if (r == EOF) SCM_RETURN(SCM_EOF);
#ifdef DOUBLE_ARMENDIAN
    if (SCM_EQ(Scm_NativeEndian(), SCM_SYM_ARM_LITTLE_ENDIAN)) {
        if (SCM_EQ(SCM_OBJ(endian), SCM_SYM_LITTLE_ENDIAN)) {

            if (eltsize == 8) {
                Scm_UVectorSwapBytesX(SCM_UVECTOR(v), SWAPB_ARM_LE);
            }
        } else if (SCM_EQ(SCM_OBJ(endian), SCM_SYM_BIG_ENDIAN)) {
            Scm_UVectorSwapBytesX(SCM_UVECTOR(v), SWAPB_ARM_BE);
        }
    } else
#endif
        {
#ifdef WORDS_BIGENDIAN
            if (SCM_EQ(SCM_OBJ(endian), SCM_SYM_LITTLE_ENDIAN)) {
                Scm_UVectorSwapBytesX(SCM_UVECTOR(v), SWAPB_STD);
            } else if (SCM_EQ(SCM_OBJ(endian), SCM_SYM_ARM_LITTLE_ENDIAN)) {
                Scm_UVectorSwapBytesX(SCM_UVECTOR(v), SWAPB_ARM_BE);
            }
#else
            if (SCM_EQ(SCM_OBJ(endian), SCM_SYM_BIG_ENDIAN)) {
                Scm_UVectorSwapBytesX(SCM_UVECTOR(v), SWAPB_STD);
            } else if (SCM_EQ(SCM_OBJ(endian), SCM_SYM_ARM_LITTLE_ENDIAN)) {
                if (eltsize == 8) {
                    Scm_UVectorSwapBytesX(SCM_UVECTOR(v), SWAPB_ARM_LE);
                }
            }
#endif
        }
    SCM_RETURN(Scm_MakeInteger((r+eltsize-1)/eltsize));
}
