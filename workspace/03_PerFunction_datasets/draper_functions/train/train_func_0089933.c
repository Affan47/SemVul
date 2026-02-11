make_iso_to_alphabet_grid(void)
{   int i, j, k; int z;

    for (j=0; j<0x100; j++)
    {   zscii_to_iso_grid[j] = 0;
        zscii_to_alphabet_grid[j] = -j;
    }

    for (j=0; j<0x100; j++)
    {   iso_to_alphabet_grid[j]=-5;
        if ((j >= 0x20) && (j <= 0x7e))
        {   iso_to_alphabet_grid[j] = -j;
            zscii_to_iso_grid[j] = j;
        }
        if ((j >= 0xa1) && (j <= 0xff))
        {   z = unicode_to_zscii(iso_to_unicode(j));
            if (character_set_setting != 0)
                zscii_to_iso_grid[z] = j;
            iso_to_alphabet_grid[j] = -z;
        }
        iso_to_unicode_grid[j] = iso_to_unicode(j);
    }
    for (j=0; j<3; j++)
        for (k=(j<2?0:1); k<26; k++)
            {   i=(int) ((alphabet[j])[k]);
                zscii_to_alphabet_grid[i] = k + j*26;
                iso_to_alphabet_grid[zscii_to_iso_grid[i]] = k + j*26;
            }
}
