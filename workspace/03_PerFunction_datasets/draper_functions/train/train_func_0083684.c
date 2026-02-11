sgf_setActiveNodeNumber(Sgf *mc, int moveNum)  {
  int  curMove = 0;
  SgfElem  *me;

  assert(MAGIC(mc));
  me = &mc->top;
  for (;;)  {
    assert(MAGIC(me));
    if (me->activeChild == NULL)  {
      assert(curMove == moveNum);
      break;
    }
    if (me->activeChild->type == sgfType_node)  {
      ++curMove;
      if (curMove > moveNum)
	break;
    }
    me = me->activeChild;
  }
  mc->active = me;
}
