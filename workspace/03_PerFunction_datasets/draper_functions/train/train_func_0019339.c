__close_mcd(word32 mcd, int32 from_vpi)
{
 register int32 i;
 int32 err;

 err = FALSE;
 if (mcd == 0L)
  {
   if (!from_vpi)
    {
     __sgfinform(431,
      "$fclose passed empty (no bits on) multi-channel descriptor");
    }
   return(bld_open_mcd());
  }
 if ((mcd & 1L) != 0)
  {
   if (!from_vpi)
    {
     __sgfinform(432,
      "$fclose bit 1 (stdout) multi-channel descriptor cannot be closed");
    }
   err = TRUE;
  }
 if ((mcd & 2L) != 0)
  {
   if (!from_vpi)
    {
     __sgfinform(432,
      "$fclose bit 2 (stderr) multi-channel descriptor cannot be closed");
    }
   err = TRUE;
  }
 for (i = 2; i < 31; i++)
  {
   if (((mcd >> i) & 1L) == 0L) continue;

   if (__mulchan_tab[i].mc_s == NULL)
    {
     if (!from_vpi)
      {
       __sgfwarn(611,
        "$fclose multi-channel descriptor bit %d on, but file already closed",
        i + 1);
      }
     err = TRUE;
     continue;
    }
   __my_fclose(__mulchan_tab[i].mc_s);
   __mulchan_tab[i].mc_s = NULL;
   __my_free(__mulchan_tab[i].mc_fnam, strlen(__mulchan_tab[i].mc_fnam) + 1);
   __mulchan_tab[i].mc_fnam = NULL;
  }
 if (!from_vpi)
  {
   if (((mcd >> 31) & 1L) != 0L)
    {
     __sgfwarn(611,
      "$fclose multi-channel descriptor bit 31 on, but no open file - unusable because reserved for new Verilog 2000 file I/O");
     err = TRUE;
    }
  }

 if (err) return(bld_open_mcd());
 return(0);
}
