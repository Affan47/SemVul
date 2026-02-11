uves_chip_tochar(enum uves_chip chip)
{
    return
    (chip == UVES_CHIP_BLUE) ? 'b' :
    (chip == UVES_CHIP_REDU) ? 'u' :
    (chip == UVES_CHIP_REDL) ? 'l' : '?';
}
