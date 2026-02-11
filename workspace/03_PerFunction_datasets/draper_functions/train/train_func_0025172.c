__get_dbg_val(void)
{
 int32 val;

 if (__toktyp != NUMBER || __itoklen > WBITS || __bcwrk[0] != 0L) return(-1);
 val = (int32) __acwrk[0];
 if (val < -1) return(-1);
 return(val);
}
