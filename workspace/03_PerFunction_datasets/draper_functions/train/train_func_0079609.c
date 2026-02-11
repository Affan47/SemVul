asm_phi_break(ASMState *as, RegSet blocked, RegSet blockedby,
			  RegSet allow)
{
  RegSet candidates = blocked & allow;
  if (candidates) {


    Reg down, up = ra_pick(as, ~blocked & allow);
    if (candidates & ~blockedby)
      candidates = candidates & ~blockedby;
    down = rset_picktop(candidates);
    ra_rename(as, down, up);
  }
}
