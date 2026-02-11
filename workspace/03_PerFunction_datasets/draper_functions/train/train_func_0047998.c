decode_modified(unsigned char *sprite_ram, int interleave)
{
    int i,offs;


    for (offs = videoram_size - 1;offs >= 0;offs--)
    {
        int code;

        code = videoram[offs] + 256 * (colorram[offs] & 3);

        switch (char_dirty[code])
        {
        case 1:
            decodechar(Machine->gfx[0],code,deco_charram,Machine->drv->gfxdecodeinfo[0].gfxlayout);
            char_dirty[code] = 2;

        case 2:
            dirtybuffer[offs] = 1;
            break;
        default:
            break;
        }
    }

    for (i = 0; i < sizeof(char_dirty)/sizeof(char_dirty[0]); i++)
    {
        if (char_dirty[i] == 2)  char_dirty[i] = 0;
    }


    for (i = 0, offs = 0;i < 8; i++, offs += 4*interleave)
    {
        int code;

        code  = sprite_ram[offs + interleave];
        if (sprite_dirty[code])
        {
            sprite_dirty[code] = 0;

            decodechar(Machine->gfx[1],code,deco_charram,Machine->drv->gfxdecodeinfo[1].gfxlayout);
        }
    }
}
