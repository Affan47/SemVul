bcemit_store(FuncState *fs, ExpDesc *var, ExpDesc *e)
{
  BCIns ins;
  if (var->k == VLOCAL) {
    fs->ls->vstack[var->u.s.aux].info |= VSTACK_VAR_RW;
    expr_free(fs, e);
    expr_toreg(fs, e, var->u.s.info);
    return;
  } else if (var->k == VUPVAL) {
    fs->ls->vstack[var->u.s.aux].info |= VSTACK_VAR_RW;
    expr_toval(fs, e);
    if (e->k <= VKTRUE)
      ins = BCINS_AD(BC_USETP, var->u.s.info, const_pri(e));
    else if (e->k == VKSTR)
      ins = BCINS_AD(BC_USETS, var->u.s.info, const_str(fs, e));
    else if (e->k == VKNUM)
      ins = BCINS_AD(BC_USETN, var->u.s.info, const_num(fs, e));
    else
      ins = BCINS_AD(BC_USETV, var->u.s.info, expr_toanyreg(fs, e));
  } else if (var->k == VGLOBAL) {
    BCReg ra = expr_toanyreg(fs, e);
    ins = BCINS_AD(BC_GSET, ra, const_str(fs, var));
  } else {
    BCReg ra, rc;
    lua_assert(var->k == VINDEXED);
    ra = expr_toanyreg(fs, e);
    rc = var->u.s.aux;
    if ((int32_t)rc < 0) {
      ins = BCINS_ABC(BC_TSETS, ra, var->u.s.info, ~rc);
    } else if (rc > BCMAX_C) {
      ins = BCINS_ABC(BC_TSETB, ra, var->u.s.info, rc-(BCMAX_C+1));
    } else {


      lua_assert(e->k != VNONRELOC || ra < fs->nactvar ||
		 rc < ra || (bcreg_free(fs, rc),1));
      ins = BCINS_ABC(BC_TSETV, ra, var->u.s.info, rc);
    }
  }
  bcemit_INS(fs, ins);
  expr_free(fs, e);
}
