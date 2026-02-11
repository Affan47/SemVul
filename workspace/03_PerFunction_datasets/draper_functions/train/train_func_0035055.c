initialize_tiff_io( SPEC * sp,
                    int    endian )
{
    if ( ! typeSize[ kUByte ] )
    {


        typeSize[ kUByte ] = typeSize[ SBYTE ] = 1;
        typeSize[ ASCII ] = 1;
        typeSize[ kShort ] = typeSize[ kUShort ] = 2;
        typeSize[ kLong ] = typeSize[ kULong ] = 4;
        typeSize[ RATIONAL ] = typeSize[ SRATIONAL ] = 8;
        typeSize[ kFloat ] = 4;
        typeSize[ kDouble ] = 8;
    }


    sp->readit[ kUByte ] = sp->readit[SBYTE] = fgetc;
    sp->writeit[ kUByte ] = sp->writeit[SBYTE] = fputc;
    sp->readit[ ASCII ] = fgetc;
    sp->writeit[ ASCII ] = fputc;

    sp->readit[ kShort ] = endian == MSBFirst ? fli_fget2MSBF : fli_fget2LSBF;
    sp->readit[ kUShort ] = endian == MSBFirst ? fli_fget2MSBF : fli_fget2LSBF;
    sp->writeit[ kUShort ] = endian == MSBFirst ? fli_fput2MSBF : fli_fput2LSBF;
    sp->writeit[ kShort ] = endian == MSBFirst ? fli_fput2MSBF : fli_fput2LSBF;

    sp->readit[ kULong ] = endian == MSBFirst ? fli_fget4MSBF : fli_fget4LSBF;
    sp->readit[ kLong ] = endian == MSBFirst ? fli_fget4MSBF : fli_fget4LSBF;
    sp->writeit[ kULong ] = endian == MSBFirst ? fli_fput4MSBF : fli_fput4LSBF;
    sp->writeit[ kLong ] = endian == MSBFirst ? fli_fput4MSBF : fli_fput4LSBF;

    sp->read2bytes = sp->readit[ kShort ];
    sp->read4bytes = sp->readit[ kLong ];
    sp->write2bytes = sp->writeit[ kShort ];
    sp->write4bytes = sp->writeit[ kLong ];
}
