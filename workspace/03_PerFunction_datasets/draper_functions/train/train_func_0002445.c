R_InitSpriteLumps(void)
{
    int i;
    patch_t *patch;

    firstspritelump = W_GetNumForName(DEH_String("S_START")) + 1;
    lastspritelump = W_GetNumForName(DEH_String("S_END")) - 1;
    numspritelumps = lastspritelump - firstspritelump + 1;
    spritewidth = Z_Malloc(numspritelumps * sizeof(fixed_t), PU_STATIC, 0);
    spriteoffset = Z_Malloc(numspritelumps * sizeof(fixed_t), PU_STATIC, 0);
    spritetopoffset = Z_Malloc(numspritelumps * sizeof(fixed_t), PU_STATIC, 0);

    for (i = 0; i < numspritelumps; i++)
    {
#ifdef __NEXT__
        if (!(i & 63))
            printf(".");
#else
        IncThermo();
#endif
        patch = W_CacheLumpNum(firstspritelump + i, PU_CACHE);
        spritewidth[i] = SHORT(patch->width) << FRACBITS;
        spriteoffset[i] = SHORT(patch->leftoffset) << FRACBITS;
        spritetopoffset[i] = SHORT(patch->topoffset) << FRACBITS;
    }
}
