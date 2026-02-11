rotation_order(ScmObj sym)
 {
   if (SCM_UNBOUNDP(sym)) return SCM_MATH3D_ROTATE_XYZ;
   if (SCM_EQ(sym, sym_xyz)) return SCM_MATH3D_ROTATE_XYZ;
   if (SCM_EQ(sym, sym_xzy)) return SCM_MATH3D_ROTATE_XZY;
   if (SCM_EQ(sym, sym_yzx)) return SCM_MATH3D_ROTATE_YZX;
   if (SCM_EQ(sym, sym_yxz)) return SCM_MATH3D_ROTATE_YXZ;
   if (SCM_EQ(sym, sym_zxy)) return SCM_MATH3D_ROTATE_ZXY;
   if (SCM_EQ(sym, sym_zyx)) return SCM_MATH3D_ROTATE_ZYX;
   Scm_Error("bad rotation order: must be either one of xyz, xzy, yzx, yxz, zxy, or zyx, but got %S", sym);
   return 0;
 }
