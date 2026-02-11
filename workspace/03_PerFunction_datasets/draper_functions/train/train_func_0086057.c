GetChiralFlag(AtomExpr *expr)
  {
    int size=0;
#define OB_EVAL_STACKSIZE 40

    AtomExpr *stack[OB_EVAL_STACKSIZE];
    memset(stack,'\0',sizeof(AtomExpr*)*OB_EVAL_STACKSIZE);
#undef OB_EVAL_STACKSIZE

    bool lftest=true;

    for (size=0,stack[size] = expr;size >= 0;expr=stack[size])
      {
        switch (expr->type)
          {
          case AE_LEAF:
            if (expr->leaf.prop == AL_CHIRAL)
              return(expr->leaf.value);
            size--;
            break;

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

          case AE_OR:

            if (stack[size+1] == expr->bin.rgt)
              size--;
            else if (stack[size+1] == expr->bin.lft)
              {
                if (!lftest)
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
            if (stack[size+1] != expr->mon.arg)
              {
                size++;
                stack[size] = expr->mon.arg;
              }
            else
              {
                lftest = !lftest;
                size--;
              }
            break;

          case AE_RECUR:
            size--;
            break;
          }
      }

    return((int)false);
  }
