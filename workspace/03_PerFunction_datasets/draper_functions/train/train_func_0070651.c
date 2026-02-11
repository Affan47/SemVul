GetCharge(int idx)
  {
    AtomExpr *expr = _pat->atom[idx].expr;

    int size=0;
    AtomExpr *stack[15];
    memset(stack,'\0',sizeof(AtomExpr*)*15);
    bool lftest=true;

    for (size=0,stack[size] = expr;size >= 0;expr=stack[size])
      {
        switch (expr->type)
          {
          case AE_LEAF:
            switch( expr->leaf.prop )
              {
              case AL_NEGATIVE:
                return(-1*(int)expr->leaf.value);
              case AL_POSITIVE:
                return((int)expr->leaf.value);
              default:
                lftest=true;
              }
            size--;
            break;

          case AE_OR:
          case AE_ANDHI:
          case AE_ANDLO:

            if (stack[size+1] == expr->bin.rgt)
              size--;
            else if (stack[size+1] == expr->bin.lft)
              {
                if (lftest)
                  {
                    size++;
                    stack[size] = expr->bin.rgt;
                  }
                else
                  size--;
              }
            else
              {
                size++;
                stack[size] = expr->bin.lft;
              }
            break;

          case AE_NOT:
            return(0);
          case AE_RECUR:
            return(0);
          }
      }

    return(0);
  }
