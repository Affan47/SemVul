writeAot(HANDLE_FDK_BITSTREAM hBitstreamBuffer, AUDIO_OBJECT_TYPE aot)
{
    int tmp = (int) aot;

    if (tmp > 31) {
        FDKwriteBits( hBitstreamBuffer, AOT_ESCAPE, 5 );
        FDKwriteBits( hBitstreamBuffer, tmp-32, 6 );
    } else {
        FDKwriteBits( hBitstreamBuffer, tmp, 5 );
    }
}
