prof_dump_until(pTHX_ long ix)
{
    long base = 0;
    struct tms t1, t2;
    clock_t realtime2;

    const clock_t realtime1 = Times(&t1);

    while (base < ix) {
	const opcode ptype = g_profstack[base++].ptype;
	if (ptype == OP_TIME) {
	    const long tms_utime = g_profstack[base++].tms_utime;
	    const long tms_stime = g_profstack[base++].tms_stime;
	    const long realtime = g_profstack[base++].realtime;

	    prof_dumpt(aTHX_ tms_utime, tms_stime, realtime);
	}
	else if (ptype == OP_GV) {
	    const U32 id = g_profstack[base++].id;
	    const char * const pname = g_profstack[base++].name;
	    const char * const gname = g_profstack[base++].name;

	    prof_dumps(aTHX_ id, pname, gname);
	}
	else {
	    const U32 id = g_profstack[base++].id;
	    prof_dumpa(aTHX_ ptype, id);
	}
    }
    PerlIO_flush(g_fp);
    realtime2 = Times(&t2);
    if (realtime2 != realtime1 || t1.tms_utime != t2.tms_utime
	|| t1.tms_stime != t2.tms_stime) {
	g_wprof_r += realtime2 - realtime1;
	g_wprof_u += t2.tms_utime - t1.tms_utime;
	g_wprof_s += t2.tms_stime - t1.tms_stime;

	PerlIO_printf(g_fp,"+ & Devel::DProf::write\n");
	PerlIO_printf(g_fp,"@ %"IVdf" %"IVdf" %"IVdf"\n",


		      (IV)(t2.tms_utime - t1.tms_utime),
		      (IV)(t2.tms_stime - t1.tms_stime),
		      (IV)(realtime2 - realtime1));
	PerlIO_printf(g_fp,"- & Devel::DProf::write\n");
	g_otms_utime = t2.tms_utime;
	g_otms_stime = t2.tms_stime;
	g_orealtime = realtime2;
	PerlIO_flush(g_fp);
    }
}
