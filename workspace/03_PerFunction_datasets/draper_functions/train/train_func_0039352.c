compare_ops (const void *pa, const void *pb)
{
  const tree opa = *((const tree *)pa);
  const tree opb = *((const tree *)pb);
  gimple opstmta = SSA_NAME_DEF_STMT (opa);
  gimple opstmtb = SSA_NAME_DEF_STMT (opb);
  basic_block bba;
  basic_block bbb;

  if (gimple_nop_p (opstmta) && gimple_nop_p (opstmtb))
    return SSA_NAME_VERSION (opa) - SSA_NAME_VERSION (opb);
  else if (gimple_nop_p (opstmta))
    return -1;
  else if (gimple_nop_p (opstmtb))
    return 1;

  bba = gimple_bb (opstmta);
  bbb = gimple_bb (opstmtb);

  if (!bba && !bbb)
    return SSA_NAME_VERSION (opa) - SSA_NAME_VERSION (opb);
  else if (!bba)
    return -1;
  else if (!bbb)
    return 1;

  if (bba == bbb)
    {
      if (gimple_code (opstmta) == GIMPLE_PHI
	  && gimple_code (opstmtb) == GIMPLE_PHI)
	return SSA_NAME_VERSION (opa) - SSA_NAME_VERSION (opb);
      else if (gimple_code (opstmta) == GIMPLE_PHI)
	return -1;
      else if (gimple_code (opstmtb) == GIMPLE_PHI)
	return 1;
      else if (gimple_uid (opstmta) != gimple_uid (opstmtb))
        return gimple_uid (opstmta) - gimple_uid (opstmtb);
      else
	return SSA_NAME_VERSION (opa) - SSA_NAME_VERSION (opb);
    }
  return rpo_numbers[bba->index] - rpo_numbers[bbb->index];
}
