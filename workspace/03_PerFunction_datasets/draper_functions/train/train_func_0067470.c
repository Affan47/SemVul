trq_get_matchv_i(Query *self, MatchVector *mv,
                                     TermVector *tv)
{
    Range *range = RQ(((ConstantScoreQuery *)self)->original)->range;
    if (tv->field == range->field) {
        double lnum = 0.0, unum = 0.0;
        int len = 0;
        const char *lt = range->lower_term;
        const char *ut = range->upper_term;
        if ((!lt
             || (sscanf(lt,"%lg%n",&lnum,&len) && (int)strlen(lt) == len))
            &&
            (!ut
             || (sscanf(ut,"%lg%n",&unum,&len) && (int)strlen(ut) == len)))
        {
            TypedRangeCheck check = TRC_NONE;
            int i = 0, j = 0;

            if (lt) {
               check = range->include_lower ? TRC_GE : TRC_GT;
            }
            if (ut) {
               check = (TypedRangeCheck)(check | (range->include_upper
                                                  ? TRC_LE
                                                  : TRC_LT));
            }

            switch(check) {
                case TRC_LE:
                    SET_TERMS(num <= unum);
                    break;
                case TRC_LT:
                    SET_TERMS(num <  unum);
                    break;
                case TRC_GE:
                    SET_TERMS(num >= lnum);
                    break;
                case TRC_GE_LE:
                    SET_TERMS(num >= lnum && num <= unum);
                    break;
                case TRC_GE_LT:
                    SET_TERMS(num >= lnum && num <  unum);
                    break;
                case TRC_GT:
                    SET_TERMS(num >  lnum);
                    break;
                case TRC_GT_LE:
                    SET_TERMS(num >  lnum && num <= unum);
                    break;
                case TRC_GT_LT:
                    SET_TERMS(num >  lnum && num <  unum);
                    break;
                case TRC_NONE:

                    assert(false);
            }

        }
        else {
            return rq_get_matchv_i(self, mv, tv);
        }
    }
    return mv;
}
