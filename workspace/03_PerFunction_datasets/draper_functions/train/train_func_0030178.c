write_z_char_z(int i)
{   uint32 j;
    ASSERT_ZCODE();
    total_zchars_trans++;
    zchars_out_buffer[zob_index++]=(i%32);
    if (zob_index!=3) return;
    zob_index=0;
    j= zchars_out_buffer[0]*0x0400 + zchars_out_buffer[1]*0x0020
       + zchars_out_buffer[2];
    if (text_out_pc+2 > text_out_limit) {
        text_out_overflow = TRUE;
        return;
    }
    text_out_pc[0] = j/256; text_out_pc[1] = j%256; text_out_pc+=2;
    total_bytes_trans+=2;
}
