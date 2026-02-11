ns_sbb_disp(_ns_sess * s, int no)
{
    if (!s)
        return NS_FAIL;

    switch (s->backend) {
#ifdef NS_HAVE_SCREEN
      case NS_MODE_SCREEN:
          ns_go2_disp(s, no);

          return ns_statement(s, "copy");
          break;
#endif
        default:
            return NS_FAIL;
    }
}
