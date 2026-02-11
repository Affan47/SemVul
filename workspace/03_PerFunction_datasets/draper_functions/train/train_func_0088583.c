dio_ReadUX(int Size) {
    switch (Size) {
    case 2:
        return dio_ReadU2();
    case 4:
        return dio_ReadU4();
    case 8:
        return dio_ReadU8();
    default:
        str_exception(ERR_INV_DWARF, "invalid data size");;
        return 0;
    }
}
