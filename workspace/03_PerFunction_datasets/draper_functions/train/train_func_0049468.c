coro_semaphore_adjust (pTHX_ AV *av, IV adjust)
{
  SV *count_sv = AvARRAY (av)[0];
  IV count = SvIVX (count_sv);

  count += adjust;
  SvIVX (count_sv) = count;


  while (count > 0 && AvFILLp (av) > 0)
    {
      SV *cb;


      AvARRAY (av)[0] = AvARRAY (av)[1];
      AvARRAY (av)[1] = count_sv;
      cb = av_shift (av);

      if (SvOBJECT (cb))
        {
          api_ready (aTHX_ cb);
          --count;
        }
      else if (SvTYPE (cb) == SVt_PVCV)
        {
          dSP;
          PUSHMARK (SP);
          XPUSHs (sv_2mortal (newRV_inc ((SV *)av)));
          PUTBACK;
          call_sv (cb, G_VOID | G_DISCARD | G_EVAL | G_KEEPERR);
        }

      SvREFCNT_dec (cb);
    }
}
