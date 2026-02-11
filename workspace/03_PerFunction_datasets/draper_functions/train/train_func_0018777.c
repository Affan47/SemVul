regclass_for_constraint (enum constraint_num c)
{
  switch (c)
    {
    case CONSTRAINT_R: return LEGACY_REGS;
    case CONSTRAINT_q: return TARGET_64BIT ? GENERAL_REGS : Q_REGS;
    case CONSTRAINT_Q: return Q_REGS;
    case CONSTRAINT_l: return INDEX_REGS;
    case CONSTRAINT_a: return AREG;
    case CONSTRAINT_b: return BREG;
    case CONSTRAINT_c: return CREG;
    case CONSTRAINT_d: return DREG;
    case CONSTRAINT_S: return SIREG;
    case CONSTRAINT_D: return DIREG;
    case CONSTRAINT_A: return AD_REGS;
    case CONSTRAINT_U: return CLOBBERED_REGS;
    case CONSTRAINT_f: return TARGET_80387 || TARGET_FLOAT_RETURNS_IN_80387 ? FLOAT_REGS : NO_REGS;
    case CONSTRAINT_t: return TARGET_80387 || TARGET_FLOAT_RETURNS_IN_80387 ? FP_TOP_REG : NO_REGS;
    case CONSTRAINT_u: return TARGET_80387 || TARGET_FLOAT_RETURNS_IN_80387 ? FP_SECOND_REG : NO_REGS;
    case CONSTRAINT_y: return TARGET_MMX ? MMX_REGS : NO_REGS;
    case CONSTRAINT_x: return TARGET_SSE ? SSE_REGS : NO_REGS;
    case CONSTRAINT_Yz: return TARGET_SSE ? SSE_FIRST_REG : NO_REGS;
    case CONSTRAINT_Y2: return TARGET_SSE2 ? SSE_REGS : NO_REGS;
    case CONSTRAINT_Yi: return TARGET_SSE2 && TARGET_INTER_UNIT_MOVES ? SSE_REGS : NO_REGS;
    case CONSTRAINT_Ym: return TARGET_MMX && TARGET_INTER_UNIT_MOVES ? MMX_REGS : NO_REGS;
    default: break;
    }
  return NO_REGS;
}
