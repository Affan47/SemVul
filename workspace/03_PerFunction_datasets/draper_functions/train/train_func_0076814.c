match(int *pn, node_id c1[], node_id c2[], State *s)
  { if (s->IsGoal())
      {
        *pn=s->CoreLen();
        s->GetCoreSet(c1, c2);
        return true;
      }

    if (s->IsDead())
      return false;

    node_id n1=NULL_NODE, n2=NULL_NODE;
    bool found=false;
    while (!found && s->NextPair(&n1, &n2, n1, n2))
      { if (s->IsFeasiblePair(n1, n2))
          { State *s1=s->Clone();
            s1->AddPair(n1, n2);
            found=match(pn, c1, c2, s1);
            s1->BackTrack();
            delete s1;
          }
      }
    return found;
  }
