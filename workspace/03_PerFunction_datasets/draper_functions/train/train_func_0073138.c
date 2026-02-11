mark_elimination (int from, int to)
{
  basic_block bb;

  FOR_EACH_BB (bb)
    {

      bitmap r = DF_LR_IN (bb);

      if (REGNO_REG_SET_P (r, from))
	{
	  CLEAR_REGNO_REG_SET (r, from);
	  SET_REGNO_REG_SET (r, to);
	}
    }
}
