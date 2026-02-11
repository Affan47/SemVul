calcNeeded(lame_global_flags* gfp)
{
    int mf_needed;

#if ENCDELAY < MDCTDELAY
# error ENCDELAY is less than MDCTDELAY, see encoder.h
#endif
#if FFTOFFSET > BLKSIZE
# error FFTOFFSET is greater than BLKSIZE, see encoder.h
#endif

    mf_needed = BLKSIZE + gfp->framesize - FFTOFFSET;

    mf_needed = Max(mf_needed, 512 + gfp->framesize - 32);

    assert(MFSIZE >= mf_needed);

    return mf_needed;
}
