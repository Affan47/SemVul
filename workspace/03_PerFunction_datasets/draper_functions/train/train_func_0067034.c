constraint_satisfied_p (rtx op, enum constraint_num c)
{
  switch (c)
    {
    case CONSTRAINT_I: return satisfies_constraint_I (op);
    case CONSTRAINT_J: return satisfies_constraint_J (op);
    case CONSTRAINT_K: return satisfies_constraint_K (op);
    case CONSTRAINT_L: return satisfies_constraint_L (op);
    case CONSTRAINT_M: return satisfies_constraint_M (op);
    case CONSTRAINT_N: return satisfies_constraint_N (op);
    case CONSTRAINT_S: return satisfies_constraint_S (op);
    case CONSTRAINT_Y: return satisfies_constraint_Y (op);
    case CONSTRAINT_Z: return satisfies_constraint_Z (op);
    case CONSTRAINT_Ush: return satisfies_constraint_Ush (op);
    case CONSTRAINT_Uss: return satisfies_constraint_Uss (op);
    case CONSTRAINT_Usd: return satisfies_constraint_Usd (op);
    case CONSTRAINT_UsM: return satisfies_constraint_UsM (op);
    case CONSTRAINT_Ui1: return satisfies_constraint_Ui1 (op);
    case CONSTRAINT_Ui3: return satisfies_constraint_Ui3 (op);
    case CONSTRAINT_Up3: return satisfies_constraint_Up3 (op);
    case CONSTRAINT_Q: return satisfies_constraint_Q (op);
    case CONSTRAINT_Ump: return satisfies_constraint_Ump (op);
    case CONSTRAINT_Utv: return satisfies_constraint_Utv (op);
    case CONSTRAINT_Ufc: return satisfies_constraint_Ufc (op);
    case CONSTRAINT_Dn: return satisfies_constraint_Dn (op);
    case CONSTRAINT_Dh: return satisfies_constraint_Dh (op);
    case CONSTRAINT_Dq: return satisfies_constraint_Dq (op);
    case CONSTRAINT_Dl: return satisfies_constraint_Dl (op);
    case CONSTRAINT_Dr: return satisfies_constraint_Dr (op);
    case CONSTRAINT_Dz: return satisfies_constraint_Dz (op);
    case CONSTRAINT_Dd: return satisfies_constraint_Dd (op);
    default: break;
    }
  return false;
}
