coro_push_av (pTHX_ AV *av, I32 gimme_v)
{
  if (AvFILLp (av) >= 0 && gimme_v != G_VOID)
    {
      dSP;

      if (gimme_v == G_SCALAR)
        XPUSHs (AvARRAY (av)[AvFILLp (av)]);
      else
        {
          int i;
          EXTEND (SP, AvFILLp (av) + 1);

          for (i = 0; i <= AvFILLp (av); ++i)
            PUSHs (AvARRAY (av)[i]);
        }

      PUTBACK;
    }
}
