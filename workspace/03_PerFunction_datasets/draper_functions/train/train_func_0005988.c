ns_go2_disp(_ns_sess * s, int d)
{
    if (!s)
        return NS_FAIL;
    if (s->curr && s->curr->index == d)
        return NS_SUCC;

    switch (s->backend) {
#ifdef NS_HAVE_SCREEN
      case NS_MODE_SCREEN:
          {


              char b[] = "select _";
              b[7] = '0' + d;
              return ns_statement(s, b);
          }
          break;
#endif
#ifdef NS_HAVE_TWIN
        case NS_MODE_TWIN:
            {
                tscreen ts = Tw_FirstScreen(s->twin);

                printf("screen: %p\n", ts);
                while (d-- && ts)
                    ts = Tw_NextObj(s->twin, ts);
                if (ts) {
                    Tw_RaiseScreen(s->twin, ts);
                    return NS_SUCC;
                }
            }
            break;
#endif
        default:
            return NS_FAIL;
    }
}
