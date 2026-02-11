z_write_header(zword i, zbyte val)
{
  zbyte diff = LOBYTE(i) ^ val;
  if(diff == 0)
    return;
  if(i >= 0x40) {
    LOBYTEwrite(i, val);
    return;
  }
  if(i != HD_FLAGS2 + 1) {
    n_show_error(E_MEMORY, "attempt to write to non-dynamic byte in header", i);
    return;
  }
  if(diff > b00000111) {
    n_show_error(E_MEMORY, "attempt to change non-dynamic bits in flags2", val);
    return;
  }
  LOBYTEwrite(i, val);
  if(diff & b00000001) {
    if(val & b00000001) {
      operand[0] = 2;
      op_output_stream();
    } else {
      operand[0] = neg(2);
      op_output_stream();
    }
  }
  if(diff & b00000010) {
    if(val & b00000010) {
      set_fixed(TRUE);
    } else {
      set_fixed(FALSE);
    }
  }
}
